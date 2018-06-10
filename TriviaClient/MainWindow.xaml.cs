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
                    this.connection = new Connection("172.29.111.107", 12345, pipe, this);
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
            });

        }

        private void View_Highscores_Button_Click(object sender, RoutedEventArgs e)
        {

        }

        private void Highscores_Back_Image_Click(object sender, MouseButtonEventArgs e)
        {
            SwitchWindow(MenuWindow);
        }

        private void Stats_Back_Image_Click(object sender, MouseButtonEventArgs e)
        {
            SwitchWindow(MenuWindow);
        }

        private void Exit_Room_Button_Click(object sender, RoutedEventArgs e)
        {

        }

        private void Close_Room_Button_Click(object sender, RoutedEventArgs e)
        {

        }

        private void Start_Game_Button_Click(object sender, RoutedEventArgs e)
        {
            
        }

        private void Choose_Join_Button_Click(object sender, RoutedEventArgs e)
        {

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

        }

        private void Winner_Button_Click(object sender, RoutedEventArgs e)
        {
            SetAllVisibilityCollapsed();
            MenuWindow.Visibility = Visibility.Visible;
        }
    }
}
