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
        private Error error;

        public MainWindow()
        {
            InitializeComponent();
            SwitchWindow(LoadingWindow);
            error = new Error();
            error.Title = "Connection Error";
            error.Message.Text = "Couldn't connect to server";
            error.Closing += OnWindowClosing;
            dynamic thread = new Thread(() => 
            {
                PipeManager pipe = new PipeManager();
                uint tries = 0;
                string[] config = System.IO.File.ReadAllLines("config.txt");
                while (tries < 25 && config.Length == 2)
                {
                    try
                    {
                        this.connection = new Connection(config[0], ToInt(config[1]), pipe, this);
                        this.Dispatcher.Invoke(() =>
                        {
                            SwitchWindow(LoginWindow);
                        });
                        break;
                    }
                    catch (Exception)
                    {
                        //Couldnt connect to server
                        tries++;
                        
                    }
                }
                if (this.connection == null)
                {
                    if(tries < 25)
                    {
                        this.Dispatcher.Invoke(() =>
                        {
                            error.Title = "Bad config file";
                            error.Message.Text = "The first line should have the host ip and the second the port";
                        });
                    }
                    this.Dispatcher.Invoke(() =>
                    {
                        error.Show();
                    });
                }
            });
            Closing += OnWindowClosing;
            thread.SetApartmentState(ApartmentState.STA);
            thread.Start();
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
            CreateRoomWindow.Visibility = Visibility.Collapsed;
            RoomAdminWindow.Visibility = Visibility.Collapsed;
            RoomMemberWindow.Visibility = Visibility.Collapsed;
            JoinRoomWindow.Visibility = Visibility.Collapsed;
            QuestionWindow.Visibility = Visibility.Collapsed;
            WinnerWindow.Visibility = Visibility.Collapsed;
            LoadingWindow.Visibility = Visibility.Collapsed;
        }

        public void RewriteTextBlock(TextBlock tb, string text)
        {
            tb.Text = text;
        }

        public void RewriteButton(Button b, string text)
        {
            b.Content = text;
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
                        ev.GetConnection().GetData().Login(username);
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
                    ev.GetConnection().GetData().Login(username);
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
            QuestionTimeout.Text = "";
            QuestionCount.Text = "";
            MaxUsers.Text = "";
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
                ev.GetConnection().GetData().Logout();
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
                    if(i == highscores.Length)
                    {
                        for(int j = i; j < 5; j++)
                        {
                            textBlocks[j].Visibility = Visibility.Collapsed;
                        }
                        break;
                    }
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
                textBlocks[i].Visibility = Visibility.Visible;
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
            connection.Send(JsonPacketRequestSerializer.GetInstance().Seriliaze(new GetStatsRequest()), (PacketEvent ev) =>
            {
                if(ev.GetResponse().GetID() != Utils.ResponseID.STATS_RESPONSE)
                {
                    return;
                }
                GetStatsResponse response = JsonPacketResponseDeserializer.GetInstance().DeserializeGetStatsResponse(ev.GetResponse().GetBuffer());
                StupidityRate.Text = "Stupidity Rate: " + (int) response.GetStupidityRate() + "%";
                WinningRate.Text = "Winning Rate: " + (int) response.GetWinRate() + "%";
                AverageTime.Text = "Average Time Per Questions: " + (int) response.GetAverageTime() + " (s)";
                CorrectAnswersRate.Text = "Correct Answers Rate: " + (int) response.GetSuccessRate() + "%";
                SwitchWindow(StatsWindow);
            });
        }

        private void Exit_Room_Button_Click(object sender, RoutedEventArgs e)
        {
            if (!connection.GetData().IsInRoom())
                return;
            LeaveRoomRequest request = new LeaveRoomRequest(connection.GetData().GetRoomId());
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

        private void ResetAdminRoom()
        {
                AdminQuestionCount.Text = "[questions] questions in this room";
                AdminAnswerTimeout.Text = "Only [time] seconds to answer";
                AdminConnectedPlayers.Text = "[players]/[max] players in the room";
        }

        private void Close_Room_Button_Click(object sender, RoutedEventArgs e)
        {
            CloseRoomRequest request = new CloseRoomRequest(connection.GetData().GetRoomId());
            connection.Send(JsonPacketRequestSerializer.GetInstance().Seriliaze(request), (PacketEvent ev) =>
            {
                if(ev.GetResponse().GetID() != Utils.ResponseID.LEAVE_ROOM_RESPONSE)
                {
                    //some error
                    return;
                }
                connection.SetListener(new MenuPacketListener());
                ResetAdminRoom();
                connection.GetData().LeaveRoom();
                SwitchWindow(MenuWindow);
            });
        }

        private void Start_Game_Button_Click(object sender, RoutedEventArgs e)
        {
            StartGameRequest request = new StartGameRequest(connection.GetData().GetRoomId());
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
                    ResetAdminRoom();
                    ev.GetConnection().GetData().LeaveRoom();
                    ev.GetConnection().SetListener(new GamePacketListener());
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
                    this.connection.Send(buffer, (PacketEvent eve) =>
                    {
                        if(eve.GetResponse().GetID() != Utils.ResponseID.GET_ROOM_STATE_RESPONSE)
                        {
                            Error win = new Error();
                            win.Title = "Join Room Error";
                            win.Message.Text = "An error occured while trying to join room";
                            if(eve.GetResponse().GetID() == Utils.ResponseID.ERROR_RESPONSE)
                            {
                                ErrorResponse res = JsonPacketResponseDeserializer.GetInstance().DeserializeErrorResponse(eve.GetResponse().GetBuffer());
                                win.Message.Text = res.GetMessage();
                            }
                            win.Show();
                            SwitchWindow(MenuWindow);
                        }
                        else
                        {
                            GetRoomStateResponse state = JsonPacketResponseDeserializer.GetInstance().DeserializeGetRoomStateResponse(eve.GetResponse().GetBuffer());
                            connection.GetData().SetTime((uint)state.GetAnswerTimeout());
                            string roomName = RoomsList.SelectedItem.ToString();
                            RoomMemberName.Text = TriviaClient.Strings.ROOM_MEMBER_NAME.Replace("[NAME]", roomName.Substring(roomName.IndexOf(' ') + 1, roomName.LastIndexOf('\'') - roomName.IndexOf(' ') - 1));
                            MemberAnswerTimeout.Text = TriviaClient.Strings.ROOM_QUESTION_TIME.Replace("[ANSWER_TIMEOUT]", state.GetAnswerTimeout() + "");
                            MemberQuestionCount.Text = TriviaClient.Strings.ROOM_QUESTION_COUNT.Replace("[QUESTIONCOUNT]", "" + state.GetQuestionCount());
                            FillRoomMemberData(state);
                            SwitchWindow(RoomMemberWindow);
                            connection.GetData().EnterRoom(ToInt(id));
                            connection.SetListener(new RoomMemberPacketListener());
                        }
                    });
                }
                RoomsList.Items.Clear();
            });
        }

        private void FillRoomMemberData(GetRoomStateResponse state)
        {
            MemberConnectedPlayers.Text = TriviaClient.Strings.ROOM_CONNECTED_PLAYERS;
            MemberConnectedPlayers.Text = MemberConnectedPlayers.Text.Replace("[PLAYERS]", state.GetPlayers().Length + "").Replace("[MAXPLAYERS]", state.GetMaxPlayers() + "");
        }

        public void FillRoomMemberData(GetPlayersInRoomResponse state)
        {
            MemberConnectedPlayers.Text = TriviaClient.Strings.ROOM_CONNECTED_PLAYERS;
            MemberConnectedPlayers.Text = MemberConnectedPlayers.Text.Replace("[PLAYERS]", state.GetPlayers().Length + "").Replace("[MAXPLAYERS]", state.GetMaxPlayers() + "");
        }

        public void FillRoomAdminData(GetPlayersInRoomResponse state)
        {
            AdminConnectedPlayers.Text = TriviaClient.Strings.ROOM_CONNECTED_PLAYERS;
            AdminConnectedPlayers.Text = AdminConnectedPlayers.Text.Replace("[PLAYERS]", state.GetPlayers().Length + "").Replace("[MAXPLAYERS]", state.GetMaxPlayers() + "");
        }


        private void Cancel_Join_Button_Click(object sender, RoutedEventArgs e)
        {
            RoomsList.Items.Clear();
            SetAllVisibilityCollapsed();
            MenuWindow.Visibility = Visibility.Visible;
        }

        private void AnswerQuestion(uint id)
        {
            Button[] answers = { Answer1, Answer2, Answer3, Answer4 };
            answers[id].Background = Brushes.Gray;
            for(int i = 0; i < 4; i++)
            {
                answers[i].IsEnabled = false;
            }
            
            SendAnswerRequest request = new SendAnswerRequest(id);
            byte[] buffer = JsonPacketRequestSerializer.GetInstance().Seriliaze(request);
            this.connection.Send(buffer, (PacketEvent ev) =>
            {
                if(ev.GetResponse().GetID() != Utils.ResponseID.SEND_ANSWER_RESPONSE)
                {
                    Console.WriteLine("Oh shittttttttt");
                    return;
                }
                SendAnswerResponse resp = JsonPacketResponseDeserializer.GetInstance().DeserializeSendAnswerResponse(ev.GetResponse().GetBuffer());
                if(resp.GetStatus() == 1)
                {
                    //Everything is fine
                }
                else
                {
                    //RUNNNN FOR YOUR LIFEEEE
                }
            });
        }

        private void Answer1_Click(object sender, RoutedEventArgs e)
        {
            AnswerQuestion(0);
        }

        private void Answer2_Click(object sender, RoutedEventArgs e)
        {
            AnswerQuestion(1);
        }

        private void Answer3_Click(object sender, RoutedEventArgs e)
        {
            AnswerQuestion(2);
        }

        private void Answer4_Click(object sender, RoutedEventArgs e)
        {
            AnswerQuestion(3);
        }

        private void Create_Room_Window_Button_Click(object sender, RoutedEventArgs e)
        {
            int maxUsers = ToInt(MaxUsers.Text), questionCount = ToInt(QuestionCount.Text), questionTimeout = ToInt(QuestionTimeout.Text);
            string username = this.connection.GetData().GetUsername();
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
                if (resp.GetID() != 0)
                {
                    ev.GetConnection().SetListener(new RoomAdminPacketListener());
                    connection.GetData().SetTime((uint)questionTimeout);
                    //We can add it so in here it will switch to the new one watch
                    string timeout = AdminAnswerTimeout.Text, people = AdminConnectedPlayers.Text, count = AdminQuestionCount.Text;
                    timeout = timeout.Replace("[time]", questionTimeout.ToString());
                    people= people.Replace("[players]/[max]", "1/" + maxUsers.ToString());
                    count = count.Replace("[questions]", questionCount.ToString());
                    AdminAnswerTimeout.Text = timeout;
                    AdminConnectedPlayers.Text = people;
                    AdminQuestionCount.Text = count;
                    SwitchWindow(RoomAdminWindow);
                    connection.GetData().EnterRoom(resp.GetID());
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
            connection.SetListener(new MenuPacketListener());
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
