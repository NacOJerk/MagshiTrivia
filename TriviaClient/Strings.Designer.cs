//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:4.0.30319.42000
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

namespace TriviaClient {
    using System;
    
    
    /// <summary>
    ///   A strongly-typed resource class, for looking up localized strings, etc.
    /// </summary>
    // This class was auto-generated by the StronglyTypedResourceBuilder
    // class via a tool like ResGen or Visual Studio.
    // To add or remove a member, edit your .ResX file then rerun ResGen
    // with the /str option, or rebuild your VS project.
    [global::System.CodeDom.Compiler.GeneratedCodeAttribute("System.Resources.Tools.StronglyTypedResourceBuilder", "15.0.0.0")]
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute()]
    [global::System.Runtime.CompilerServices.CompilerGeneratedAttribute()]
    internal class Strings {
        
        private static global::System.Resources.ResourceManager resourceMan;
        
        private static global::System.Globalization.CultureInfo resourceCulture;
        
        [global::System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1811:AvoidUncalledPrivateCode")]
        internal Strings() {
        }
        
        /// <summary>
        ///   Returns the cached ResourceManager instance used by this class.
        /// </summary>
        [global::System.ComponentModel.EditorBrowsableAttribute(global::System.ComponentModel.EditorBrowsableState.Advanced)]
        internal static global::System.Resources.ResourceManager ResourceManager {
            get {
                if (object.ReferenceEquals(resourceMan, null)) {
                    global::System.Resources.ResourceManager temp = new global::System.Resources.ResourceManager("TriviaClient.Strings", typeof(Strings).Assembly);
                    resourceMan = temp;
                }
                return resourceMan;
            }
        }
        
        /// <summary>
        ///   Overrides the current thread's CurrentUICulture property for all
        ///   resource lookups using this strongly typed resource class.
        /// </summary>
        [global::System.ComponentModel.EditorBrowsableAttribute(global::System.ComponentModel.EditorBrowsableState.Advanced)]
        internal static global::System.Globalization.CultureInfo Culture {
            get {
                return resourceCulture;
            }
            set {
                resourceCulture = value;
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to [POS]. [NAME]: [SCORE].
        /// </summary>
        internal static string HIGHSCORE_USER_FORMAT {
            get {
                return ResourceManager.GetString("HIGHSCORE_USER_FORMAT", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to [PLAYERS]/[MAXPLAYERS] players in the room.
        /// </summary>
        internal static string ROOM_CONNECTED_PLAYERS {
            get {
                return ResourceManager.GetString("ROOM_CONNECTED_PLAYERS", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to [NAME]&apos;s.
        /// </summary>
        internal static string ROOM_MEMBER_NAME {
            get {
                return ResourceManager.GetString("ROOM_MEMBER_NAME", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to [QUESTIONCOUNT] questions in this room.
        /// </summary>
        internal static string ROOM_QUESTION_COUNT {
            get {
                return ResourceManager.GetString("ROOM_QUESTION_COUNT", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Only [ANSWER_TIMEOUT] seconds to answer.
        /// </summary>
        internal static string ROOM_QUESTION_TIME {
            get {
                return ResourceManager.GetString("ROOM_QUESTION_TIME", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Average Time Per Questions: [TIME]s.
        /// </summary>
        internal static string STATS_AVERAGE_TIME {
            get {
                return ResourceManager.GetString("STATS_AVERAGE_TIME", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Correct Answers Rate: [RATE]%.
        /// </summary>
        internal static string STATS_CORRECT_ANSWER_RATE {
            get {
                return ResourceManager.GetString("STATS_CORRECT_ANSWER_RATE", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Stupidity Rate: [RATE]%.
        /// </summary>
        internal static string STATS_STUIPIDITY_RATE {
            get {
                return ResourceManager.GetString("STATS_STUIPIDITY_RATE", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Winning Rate: [RATE]%.
        /// </summary>
        internal static string STATS_WINNING_RATE {
            get {
                return ResourceManager.GetString("STATS_WINNING_RATE", resourceCulture);
            }
        }
    }
}
