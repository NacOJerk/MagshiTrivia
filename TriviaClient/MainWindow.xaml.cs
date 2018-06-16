using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using TriviaClient.Connections;
using TriviaClient.infrastructure;
using TriviaClient.Requests;
using TriviaClient.Responses;
using TriviaClient.Events;
using System.ComponentModel;
using System.Threading;

namespace TriviaClient
{
    public partial class MainWindow : Window
    {
        private Connection connection;

        public MainWindow()
        {
            InitializeComponent();
            SwitchWindow(LoadingWindow);
            dynamic thread = new Thread(() => 
            {
                PipeManager pipe = new PipeManager();
                try
                {
                    this.connection = new Connection("127.0.0.1", 12345, pipe, this);
                }
                catch(Exception)
                {
                    //Couldnt connect to server
                    Error error = new Error();
                    error.Title = "Connection Error";
                    error.Message.Text = "Couldn't connect to server";
                    error.Show();
                    while (error.IsActive) ;
                    return;
                }
                this.Dispatcher.Invoke(() =>
                {
                    SwitchWindow(LoginWindow);
                });

            });
            thread.SetApartmentState(ApartmentState.STA);
            thread.Start();
            Closing += OnWindowClosing;
        }
        public void OnWindowClosing(object sender, CancelEventArgs e)
        {
            Environment.Exit(0);
        }


        public void SwitchWindow(Canvas c)
        {
            SetAllVisibilityCollapsed();
            c.Visibility = Visibility.Visible;
        }

        private void SetAllVisibilityCollapsed()
        {
            LoginWindow.Visibility = Visibility.Collapsed;
            SignupWindow.Visibility = Visibility.Collapsed;
            MenuWindow.Visibility = Visibility.Collapsed;
            StatsWindow.Visibility = Visibility.Collapsed;
            HighscoresWindow.Visibility = Visibility.Collapsed;
            RoomAdminWindow.Visibility = Visibility.Collapsed;
            RoomMemberWindow.Visibility = Visibility.Collapsed;
            JoinRoomWindow.Visibility = Visibility.Collapsed;
            QuestionWindow.Visibility = Visibility.Collapsed;
            WinnerWindow.Visibility = Visibility.Collapsed;
            LoadingWindow.Visibility = Visibility.Collapsed;
        }

        private void Login_Button_Click(object sender, RoutedEventArgs e)
        {
            string username = LoginUsername.Text;
            string password = LoginPassword.Password;
            LoginPassword.Password = "";
            LoginUsername.Text = "";
            if (username.Length != 0 && password.Length != 0)
            {
                LoginRequest request = new LoginRequest(username, password);
                byte[] data = JsonPacketRequestSerializer.GetInstance().Seriliaze(request);
                this.connection.Send(data, (PacketEvent ev) =>
                {
                    if (ev.GetResponse().GetID() != Utils.ResponseID.LOGIN_RESPONSE)
                    {
                    //IDK this is some kind of error or something dont want to handle it now
                    return;
                    }
                    LoginResponse resp = JsonPacketResponseDeserializer.GetInstance().DeserializeLoginResponse(ev.GetResponse().GetBuffer());
                    
                    if (resp.GetStatus() == 1)
                    {
                        ev.GetConnection().getData().Login(username);
                        ev.GetConnection().SetListener(new MenuPacketListener());
                    //We can add it so in here it will switch to the new one watch

                        ev.GetMainWindow().MenuUsername.Text = username;
                        SwitchWindow(MenuWindow);
                    }
                });
            }
        }

        private void Signup_Text_Click(object sender, RoutedEventArgs e)
        {
            LoginPassword.Password = "";
            LoginUsername.Text = "";
            SetAllVisibilityCollapsed();
            SignupWindow.Visibility = Visibility.Visible;
        }

        private void Signup_Button_Click(object sender, RoutedEventArgs e)
        {
            string username = SignupUsername.Text, password = SignupPassword.Password, email = SignupEmail.Text;
            SignupEmail.Text = "";
            SignupPassword.Password = "";
            SignupUsername.Text = "";

            SignupRequest req = new SignupRequest(username, password, email);
            byte[] buff = JsonPacketRequestSerializer.GetInstance().Seriliaze(req);
            this.connection.Send(buff, (PacketEvent ev) =>
            {
                if(ev.GetResponse().GetID() != Utils.ResponseID.SIGNUP_RESPONSE)
                {
                    //IDK this is some kind of error or something dont want to handle it now
                    return;
                }
                SignupResponse resp = JsonPacketResponseDeserializer.GetInstance().DeserializeSignupResponse(ev.GetResponse().GetBuffer());
                if (resp.GetStatus() == 1)
                {
                    ev.GetConnection().getData().Login(username);
                    ev.GetConnection().SetListener(new MenuPacketListener());
                    //We can add it so in here it will switch to the new one watch

                    ev.GetMainWindow().MenuUsername.Text = username;
                    SwitchWindow(MenuWindow);

                }
                else
                {
                    Error win = new Error();
                    win.Title = "Signup Error!";
                    win.Message.Text = "Invalid username or email (username might be taken)";
                    win.Show();
                    win.Close();
                }
            });
        }

        private void Login_Text_Click(object sender, MouseButtonEventArgs e)
        {
            SignupUsername.Text = "";
            SignupPassword.Password = "";
            SignupEmail.Text = "";
            SwitchWindow(LoginWindow);
        }

        private void Join_Room_Button_Click(object sender, RoutedEventArgs e)
        {
            byte[] buff = JsonPacketRequestSerializer.GetInstance().Seriliaze(new GetRoomsRequest());
            this.connection.Send(buff, (PacketEvent ev) =>
            {
                if (ev.GetResponse().GetID() != Utils.ResponseID.GET_ROOMS_RESPONSE)
                { }
                else
                {
                    GetRoomsResponse gety = JsonPacketResponseDeserializer.GetInstance().DeserializeGetRoomsResponse(ev.GetResponse().GetBuffer());
                    if (gety.GetStatus() == 1)
                    {
                        foreach (Room r in gety.GetRooms())
                        {
                            string stats = r.GetID() + ") " + r.GetAdmin() + "'s Room: " + r.GetNumPlayers().ToString() + "/" + r.GetMaxPlayers().ToString();
                            RoomsList.Items.Add(stats);
                        }
                        SwitchWindow(JoinRoomWindow);
                    }
                    else
                    {
                        Error win = new Error();
                        win.Title = "Join Room Error";
                        win.Message.Text = "Error getting rooms list from the server";
                        win.Show();
                    }
                }
            });
        }

        private void Create_Room_Button_Click(object sender, RoutedEventArgs e)
        {
            SwitchWindow(CreateRoomWindow);
        }

        private void Logout_Button_Click(object sender, RoutedEventArgs e)
        {
            byte[] buff = JsonPacketRequestSerializer.GetInstance().Seriliaze(new SignoutRequest());
            connection.Send(buff, (PacketEvent ev) =>
            {
                LogoutResponse resp = JsonPacketResponseDeserializer.GetInstance().DeserializeLogoutResponse(ev.GetResponse().GetBuffer());
                ev.GetConnection().SetListener(null);
                ev.GetMainWindow().SwitchWindow(LoginWindow);
                ev.GetConnection().getData().Logout();
            });

        }
        
        private void ClearStats()
        {
            StupidityRate.Text = "Stupidity Rate: 100%";
            WinningRate.Text = "Winning Rate: 100%";
            AverageTime.Text = "Average Time Per Questions: 0.0";
            CorrectAnswersRate.Text = "Correct Answers Rate: 100%";
        }

        private void View_Highscores_Button_Click(object sender, RoutedEventArgs e)
        {
            GetHighscoresRequest request = new GetHighscoresRequest();
            connection.Send(JsonPacketRequestSerializer.GetInstance().Seriliaze(request), (PacketEvent ev) =>
            {
                if(ev.GetResponse().GetID() != Utils.ResponseID.HIGHSCORE_RESPONSE)
                {
                    //some error
                    return;
                }
                GetHighscoresResponse resp = JsonPacketResponseDeserializer.GetInstance().DeserializeGetHighscoresResponse(ev.GetResponse().GetBuffer());
                Dictionary<string, string>[] highscores = resp.GetHighscores();
                TextBlock[] textBlocks = { HighscoresFirst, HighscoresSecond, HighscoresThird, HighscoresForth, HighscoresFifth };
                for(int i = 0; i < 5; i++)
                {
                    textBlocks[i].Text = (i + 1) + ". " + highscores[i]["name"] + ": " + highscores[i]["score"];
                }
                ClearStats();
                SwitchWindow(HighscoresWindow);
            });
        }

        private void Highscores_Back_Image_Click(object sender, MouseButtonEventArgs e)
        {
            TextBlock[] textBlocks = { HighscoresFirst, HighscoresSecond, HighscoresThird, HighscoresForth, HighscoresFifth };
            for (int i = 0; i < 5; i++)
            {
                textBlocks[i].Text = (i + 1) + ". Username: 0";
            }
            SwitchWindow(MenuWindow);
        }

        private void Stats_Back_Image_Click(object sender, MouseButtonEventArgs e)
        {
            ClearStats();
            SwitchWindow(MenuWindow);
        }

        private void Stats_Image_Click(object sender, MouseButtonEventArgs e)
        {
            
        }

        private void Exit_Room_Button_Click(object sender, RoutedEventArgs e)
        {
            if (!connection.getData().IsInRoom())
                return;
            LeaveRoomRequest request = new LeaveRoomRequest(connection.getData().GetRoomId());
            connection.Send(JsonPacketRequestSerializer.GetInstance().Seriliaze(request), (PacketEvent ev) =>
            {
                if(ev.GetResponse().GetID() != Utils.ResponseID.LEAVE_ROOM_RESPONSE)
                {
                    //some error
                    return;
                }
                new RoomMemberPacketListener().LeaveRoom(ev);
            });
        }

        private void Close_Room_Button_Click(object sender, RoutedEventArgs e)
        {
            CloseRoomRequest request = new CloseRoomRequest(connection.getData().GetRoomId());
            connection.Send(JsonPacketRequestSerializer.GetInstance().Seriliaze(request), (PacketEvent ev) =>
            {
                if(ev.GetResponse().GetID() != Utils.ResponseID.CLOSE_ROOM_RESPONSE)
                {
                    //some error
                    return;
                }
                connection.SetListener(new MenuPacketListener());
                AdminQuestionCount.Text = "[questionCount] questions in this room";
                AdminAnswerTimeout.Text = "Only [answerTimeout] seconds to answer";
                AdminConnectedPlayers.Text = "[players]/[maxPlayers] players in the room";
                connection.getData().LeaveRoom();
                SwitchWindow(MenuWindow);
            });
        }

        private void Start_Game_Button_Click(object sender, RoutedEventArgs e)
        {
            StartGameRequest request = new StartGameRequest(connection.getData().GetRoomId());
            connection.Send(JsonPacketRequestSerializer.GetInstance().Seriliaze(request), (PacketEvent ev) =>
            {
                if(ev.GetResponse().GetID() != Utils.ResponseID.START_GAME_RESPONSE)
                {
                    //some error
                    return;
                }
                StartGameResponse resp = JsonPacketResponseDeserializer.GetInstance().DeserializeStartGameResponse(ev.GetResponse().GetBuffer());
                if(resp.GetStatus() == 0)
                {
                    Error win = new Error();
                    win.Title = "Start Game Error";
                    win.Message.Text = "We're having problems starting the game";
                    win.Show();
                }
                else
                {
                    LoadingMessage.Text = "Starting game";
                    SwitchWindow(LoadingWindow);
                }
            });
        }

        private void Choose_Join_Button_Click(object sender, RoutedEventArgs e)
        {
            string id = RoomsList.SelectedValue.ToString();
            id = id.Split(')')[0];
            JoinRoomRequest request = new JoinRoomRequest(ToInt(id));
            byte[] buff = JsonPacketRequestSerializer.GetInstance().Seriliaze(request);
            this.connection.Send(buff, (PacketEvent ev) =>
            {
                if (ev.GetResponse().GetID() != Utils.ResponseID.JOIN_ROOM_RESPONSE)
                {
                    //some error
                    return;
                }
                JoinRoomResponse resp = JsonPacketResponseDeserializer.GetInstance().DeserializeJoinRoomResponse(ev.GetResponse().GetBuffer());
                if (resp.GetStatus() == 0)
                {
                    Error win = new Error();
                    win.Title = "Join Room Error";
                    win.Message.Text = "An error occured while trying to join room";
                    win.Show();
                    SwitchWindow(MenuWindow);
                }
                else
                {
                    GetRoomStateRequest req = new GetRoomStateRequest(ToInt(id));
                    byte[] buffer = JsonPacketRequestSerializer.GetInstance().Seriliaze(req);
                    this.connection.Send(buff, (PacketEvent eve) =>
                    {
                        if(eve.GetResponse().GetID() != Utils.ResponseID.GET_ROOM_STATE_RESPONSE)
                        {
                            Error win = new Error();
                            win.Title = "Join Room Error";
                            win.Message.Text = "An error occured while trying to join room";
                            win.Show();
                            SwitchWindow(MenuWindow);
                        }
                        else
                        {
                            GetRoomStateResponse state = JsonPacketResponseDeserializer.GetInstance().DeserializeGetRoomStateResponse(eve.GetResponse().GetBuffer());
                            string roomName = RoomsList.SelectedItem.ToString();
                            RoomMemberName.Text = roomName.Substring(roomName.IndexOf(' ')+1, roomName.LastIndexOf('\'') - roomName.IndexOf(' ') - 1) + "'s";
                            MemberAnswerTimeout.Text = MemberAnswerTimeout.Text.Replace("[answerTimeout]", "" + state.GetAnswerTimeout());
                            MemberQuestionCount.Text = MemberQuestionCount.Text.Replace("[questionCount]", "" + state.GetQuestionCount());
                            MemberConnectedPlayers.Text = MemberConnectedPlayers.Text.Replace("[players]/[maxPlayers]", roomName.Substring(roomName.LastIndexOf(' ') + 1));
                            SwitchWindow(RoomMemberWindow);
                            connection.getData().EnterRoom(ToInt(id));
                            connection.SetListener(new RoomMemberPacketListener());
                        }
                    });
                }
                RoomsList.Items.Clear();
            });
        }

        private void Cancel_Join_Button_Click(object sender, RoutedEventArgs e)
        {
            RoomsList.Items.Clear();
            SetAllVisibilityCollapsed();
            MenuWindow.Visibility = Visibility.Visible;
        }

        private void AnswerQuestion(string answer)
        {

        }

        private void Answer1_Click(object sender, RoutedEventArgs e)
        {
            AnswerQuestion(Answer1.ContentStringFormat);
        }

        private void Answer2_Click(object sender, RoutedEventArgs e)
        {
            AnswerQuestion(Answer2.ContentStringFormat);
        }

        private void Answer3_Click(object sender, RoutedEventArgs e)
        {
            AnswerQuestion(Answer3.ContentStringFormat);
        }

        private void Answer4_Click(object sender, RoutedEventArgs e)
        {
            AnswerQuestion(Answer4.ContentStringFormat);
        }

        private void Create_Room_Window_Button_Click(object sender, RoutedEventArgs e)
        {
            int maxUsers = ToInt(MaxUsers.Text), questionCount = ToInt(QuestionCount.Text), questionTimeout = ToInt(QuestionTimeout.Text);
            string username = this.connection.getData().GetUsername();
            CreateRoomRequest request = new CreateRoomRequest(username, maxUsers, questionCount, questionTimeout);
            byte[] buff = JsonPacketRequestSerializer.GetInstance().Seriliaze(request);
            this.connection.Send(buff, (PacketEvent ev) =>
            {
                if (ev.GetResponse().GetID() != Utils.ResponseID.CREATE_ROOM_RESPONSE)
                {
                    //IDK this is some kind of error or something dont want to handle it now
                    return;
                }
                CreateRoomResponse resp = JsonPacketResponseDeserializer.GetInstance().DeserializeCreateRoomResponse(ev.GetResponse().GetBuffer());
                if (resp.GetID() != -1)
                {
                    ev.GetConnection().SetListener(new RoomAdminPacketListener());
                    //We can add it so in here it will switch to the new one watch
                    string timeout = AdminAnswerTimeout.Text, people = AdminConnectedPlayers.Text, count = AdminQuestionCount.Text;
                    timeout.Replace("[time]", questionTimeout.ToString());
                    people.Replace("[players]/[max]", "1/" + maxUsers.ToString());
                    count.Replace("[questions]", questionCount.ToString());
                    AdminAnswerTimeout.Text = timeout;
                    AdminConnectedPlayers.Text = people;
                    AdminQuestionCount.Text = count;
                    SwitchWindow(RoomAdminWindow);
                    connection.getData().EnterRoom(resp.GetID());
                }
                else
                {
                    Error win = new Error();
                    win.Title = "Create Room Error!";
                    win.Message.Text = "something";
                    win.Show();
                    win.Close();
                }
            });
        }

        private void Winner_Button_Click(object sender, RoutedEventArgs e)
        {
            connection.SetListener(new MenuPacketListener);
            SetAllVisibilityCollapsed();
            MenuWindow.Visibility = Visibility.Visible;
        }
        private int ToInt(string text)
        {
            int num = 0;
            foreach(char c in text)
            {
                num *= 10;
                num += c - '0';
            }
            return num;
        }
    }
}
