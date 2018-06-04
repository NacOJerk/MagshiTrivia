﻿using System;
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

namespace TriviaClient
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
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
        }

        private void Login_Button_Click(object sender, RoutedEventArgs e)
        {

        }

        private void Signup_Text_Click(object sender, RoutedEventArgs e)
        {

        }

        private void Signup_Button_Click(object sender, RoutedEventArgs e)
        {

        }

        private void Login_Text_Click(object sender, MouseButtonEventArgs e)
        {

        }

        private void Join_Room_Button_Click(object sender, RoutedEventArgs e)
        {

        }

        private void Create_Room_Button_Click(object sender, RoutedEventArgs e)
        {

        }

        private void Logout_Button_Click(object sender, RoutedEventArgs e)
        {

        }

        private void Stats_Image_Click(object sender, MouseButtonEventArgs e)
        {

        }

        private void View_Highscores_Button_Click(object sender, RoutedEventArgs e)
        {

        }

        private void Highscores_Back_Image_Click(object sender, MouseButtonEventArgs e)
        {

        }

        private void Stats_Back_Image_Click(object sender, MouseButtonEventArgs e)
        {

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

        }

        private void Answer1_Click(object sender, RoutedEventArgs e)
        {

        }

        private void Answer2_Click(object sender, RoutedEventArgs e)
        {

        }

        private void Answer3_Click(object sender, RoutedEventArgs e)
        {

        }

        private void Answer4_Click(object sender, RoutedEventArgs e)
        {

        }
    }
}