using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using TriviaClient.Responses;
using System.Windows.Controls;

namespace TriviaClient.Events
{
    class GamePacketListener : IPacketListener
    {

        private void ResetQuestionWindow(PacketEvent e)
        {
            e.GetMainWindow().Dispatcher.BeginInvoke((Action)delegate ()
            {
                e.GetMainWindow().RewriteButton(e.GetMainWindow().Answer1, "Answer 1");
                e.GetMainWindow().RewriteButton(e.GetMainWindow().Answer2, "Answer 2");
                e.GetMainWindow().RewriteButton(e.GetMainWindow().Answer3, "Answer 3");
                e.GetMainWindow().RewriteButton(e.GetMainWindow().Answer4, "Answer 4");
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
            
                string position = e.GetMainWindow().WinnerPosition.Text;
                position.Replace("0", resp.GetPosition().ToString());
            
                e.GetMainWindow().RewriteTextBlock(e.GetMainWindow().WinnerName, resp.GetWinner());
                e.GetMainWindow().RewriteTextBlock(e.GetMainWindow().WinnerPosition, position);
                e.GetMainWindow().SwitchWindow(e.GetMainWindow().WinnerWindow);
            });
            ResetQuestionWindow(e);
            
        }

        [PacketHandler(Utils.ResponseID.LOGOUT_RESPONSE)]
        public void Logout(PacketEvent e)
        {
            e.GetConnection().GetData().Logout();
            e.GetMainWindow().Dispatcher.BeginInvoke((Action)delegate ()
            {
                ResetQuestionWindow(e);
                e.GetMainWindow().RewriteTextBlock(e.GetMainWindow().MenuUsername, "");
                e.GetMainWindow().SwitchWindow(e.GetMainWindow().LoginWindow);
            });
        }

        [PacketHandler(Utils.ResponseID.SEND_QUESTION_RESPONSE)]
        public void GetQuestion(PacketEvent e)
        {
            e.GetMainWindow().Dispatcher.BeginInvoke((Action)delegate ()
            {
                SendQuestionResponse resp = JsonPacketResponseDeserializer.GetInstance().DeserializeSendQuestionResponse(e.GetResponse().GetBuffer());

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
