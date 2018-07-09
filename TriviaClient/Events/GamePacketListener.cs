using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Media;
using TriviaClient.Responses;
using System.Windows.Controls;
using System.Threading;

namespace TriviaClient.Events
{
    class GamePacketListener : IPacketListener
    {
        private void ResetButtons(PacketEvent e)
        {
            e.GetMainWindow().Dispatcher.BeginInvoke((Action)delegate ()
            {
                Button[] buttons = { e.GetMainWindow().Answer1, e.GetMainWindow().Answer2, e.GetMainWindow().Answer3, e.GetMainWindow().Answer4 };
                for (int i = 0; i < 4; i++)
                {
                    buttons[i].IsEnabled = true;
                    buttons[i].Background = new SolidColorBrush(Color.FromRgb(221, 221, 221));
                }
            });
        }


        private void ResetQuestionWindow(PacketEvent e)
        {
            ResetButtons(e);
            e.GetMainWindow().Dispatcher.BeginInvoke((Action)delegate ()
            {
                Button[] buttons = { e.GetMainWindow().Answer1, e.GetMainWindow().Answer2, e.GetMainWindow().Answer3, e.GetMainWindow().Answer4 };
                for(int i = 0; i < 4; i++)
                {
                    e.GetMainWindow().RewriteButton(buttons[i], "Answer " + i.ToString());
                }
                e.GetMainWindow().RewriteTextBlock(e.GetMainWindow().Question, "Enter question here please");
                e.GetMainWindow().RewriteTextBlock(e.GetMainWindow().Timer, "00:00");
            });
        }

        [PacketHandler(Utils.ResponseID.SEND_RESULTS_RESPONSE)]
        public void Results(PacketEvent e)
        {
            e.GetMainWindow().Dispatcher.BeginInvoke((Action)delegate ()
            {
                SendResultsResponse resp = JsonPacketResponseDeserializer.GetInstance().DeserializeSendResultsResponse(e.GetResponse().GetBuffer());
            
                e.GetMainWindow().WinnerPosition.Text = e.GetMainWindow().WinnerPosition.Text.Replace("0", (resp.GetPosition() + 1) + "");
                e.GetMainWindow().RewriteTextBlock(e.GetMainWindow().WinnerName, resp.GetWinner());
                e.GetMainWindow().SwitchWindow(e.GetMainWindow().WinnerWindow);
            });
            ResetQuestionWindow(e);
            
        }

        [PacketHandler(Utils.ResponseID.LOGOUT_RESPONSE)]
        public void Logout(PacketEvent e)
        {
            e.GetConnection().GetData().Logout();
            ResetQuestionWindow(e);
            e.GetMainWindow().Dispatcher.BeginInvoke((Action)delegate ()
            {
                e.GetMainWindow().RewriteTextBlock(e.GetMainWindow().MenuUsername, "");
                e.GetMainWindow().SwitchWindow(e.GetMainWindow().LoginWindow);
            });
        }

        [PacketHandler(Utils.ResponseID.SEND_QUESTION_RESPONSE)]
        public void GetQuestion(PacketEvent e)
        {
            dynamic thread = new Thread(() =>
            {
                e.GetConnection().GetData().IncreateTimeThread();
                uint timerId = e.GetConnection().GetData().GetTimerThread();
                uint timer = e.GetConnection().GetData().GetTime();
                do
                {
                    e.GetMainWindow().Dispatcher.BeginInvoke((Action)delegate ()
                    {
                        e.GetMainWindow().RewriteTextBlock(e.GetMainWindow().Timer, timer.ToString());
                    });
                    timer--;
                    Thread.Sleep(1000);
                } while (timer > 0 && timerId == e.GetConnection().GetData().GetTimerThread());
            });
            thread.SetApartmentState(ApartmentState.STA);
            thread.Start();
            e.GetMainWindow().Dispatcher.BeginInvoke((Action)delegate ()
            {
                SendQuestionResponse resp = JsonPacketResponseDeserializer.GetInstance().DeserializeSendQuestionResponse(e.GetResponse().GetBuffer());

                ResetButtons(e);

                string[] answers = resp.GetAnswers();
                Button[] buttons = { e.GetMainWindow().Answer1, e.GetMainWindow().Answer2, e.GetMainWindow().Answer3, e.GetMainWindow().Answer4 };
                for (int i = 0; i < 4; i++)
                {
                    e.GetMainWindow().RewriteButton(buttons[i], answers[i]);
                }
                e.GetMainWindow().RewriteTextBlock(e.GetMainWindow().Question, resp.GetQuestion());
                e.GetMainWindow().SwitchWindow(e.GetMainWindow().QuestionWindow);
            });
        }
    }
}
