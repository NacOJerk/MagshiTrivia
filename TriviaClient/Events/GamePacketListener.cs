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
            e.GetMainWindow().RewriteButton(e.GetMainWindow().Answer1, "Answer 1");
            e.GetMainWindow().RewriteButton(e.GetMainWindow().Answer2, "Answer 2");
            e.GetMainWindow().RewriteButton(e.GetMainWindow().Answer3, "Answer 3");
            e.GetMainWindow().RewriteButton(e.GetMainWindow().Answer4, "Answer 4");
            e.GetMainWindow().RewriteTextBlock(e.GetMainWindow().Question, "Enter question here please");
            e.GetMainWindow().RewriteTextBlock(e.GetMainWindow().Timer, "00:00");
        }

        [PacketHandler(Utils.ResponseID.SEND_RESULTS_RESPONSE)]
        public void Results(PacketEvent e)
        {
            SendResultsResponse resp = JsonPacketResponseDeserializer.GetInstance().DeserializeSendResultsResponse(e.GetResponse().GetBuffer());
            e.GetMainWindow().RewriteTextBlock(e.GetMainWindow().WinnerName, resp.GetWinner());
            string position = e.GetMainWindow().WinnerPosition.Text;
            position.Replace("0", resp.GetPosition().ToString());
            e.GetMainWindow().RewriteTextBlock(e.GetMainWindow().WinnerPosition, position);
            ResetQuestionWindow(e);
            e.GetMainWindow().SwitchWindow(e.GetMainWindow().WinnerWindow);
        }

        [PacketHandler(Utils.ResponseID.LOGOUT_RESPONSE)]
        public void Logout(PacketEvent e)
        {
            ResetQuestionWindow(e);
            e.GetConnection().GetData().Logout();
            e.GetMainWindow().RewriteTextBlock(e.GetMainWindow().MenuUsername, "");
            e.GetMainWindow().SwitchWindow(e.GetMainWindow().LoginWindow);
        }

        [PacketHandler(Utils.ResponseID.SEND_QUESTION_RESPONSE)]
        public void GetQuestion(PacketEvent e)
        {
            SendQuestionResponse resp = JsonPacketResponseDeserializer.GetInstance().DeserializeSendQuestionResponse(e.GetResponse().GetBuffer());
            e.GetMainWindow().RewriteTextBlock(e.GetMainWindow().Question, resp.GetQuestion());
            string[] answers = resp.GetAnswers();
            Button[] buttons = { e.GetMainWindow().Answer1, e.GetMainWindow().Answer2, e.GetMainWindow().Answer3, e.GetMainWindow().Answer4 };
            for(int i = 0; i < 4; i++)
            {
                e.GetMainWindow().RewriteButton(buttons[i], answers[i]);
            }
            e.GetMainWindow().SwitchWindow(e.GetMainWindow().QuestionWindow);
        }
    }
}
