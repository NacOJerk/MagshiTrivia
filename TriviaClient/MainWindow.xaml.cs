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

namespace TriviaClient
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private Connection connection;

        public MainWindow()
        {
            InitializeComponent();
            PipeManager pipe = new PipeManager();
            this.connection = new Connection("asd", 123,pipe, this);
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
        }

        private void Login_Button_Click(object sender, RoutedEventArgs e)
        {
            string username = LoginUsername.Text;
            string password = LoginPassword.Password;
            LoginPassword.Password = "";
            LoginUsername.Text = "";
            LoginRequest request = new LoginRequest(username, password);
            byte[] data = JsonPacketRequestSerializer.GetInstance().Seriliaze(request);
            this.connection.Send(data, (PacketEvent ev) => {
                if(ev.GetResponse().GetID() != Utils.ResponseID.LOGIN_RESPONSE)
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
                    ev.GetMainWindow().SwitchWindow(ev.GetMainWindow().MenuWindow);
                    
                }
            });
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

        }

        private void Login_Text_Click(object sender, MouseButtonEventArgs e)
        {
            SignupUsername.Text = "";
            SignupPassword.Password = "";
            SignupEmail.Text = "";
            SetAllVisibilityCollapsed();
            LoginWindow.Visibility = Visibility.Visible;
        }

        private void Join_Room_Button_Click(object sender, RoutedEventArgs e)
        {

        }

        private void Create_Room_Button_Click(object sender, RoutedEventArgs e)
        {
            SetAllVisibilityCollapsed();
            CreateRoomWindow.Visibility = Visibility.Visible;
        }

        private void Logout_Button_Click(object sender, RoutedEventArgs e)
        {

        }

        private void View_Highscores_Button_Click(object sender, RoutedEventArgs e)
        {

        }

        private void Highscores_Back_Image_Click(object sender, MouseButtonEventArgs e)
        {
            SetAllVisibilityCollapsed();
            MenuWindow.Visibility = Visibility.Visible;
        }

        private void Stats_Back_Image_Click(object sender, MouseButtonEventArgs e)
        {
            SetAllVisibilityCollapsed();
            MenuWindow.Visibility = Visibility.Visible;
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
