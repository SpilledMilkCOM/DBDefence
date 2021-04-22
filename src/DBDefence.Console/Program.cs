using DBDefense.Database;
using Fclp;
using System;
using System.Linq;
using System.Runtime.InteropServices;

namespace DBDefence.ConsoleApp {
    unsafe class Program {
        public delegate void Callback([MarshalAs(UnmanagedType.LPWStr)] String msg, int code);

        // Please pay attention to the platform!  

        const string DLL_FOLDER = @"C:\tmp\DbDefence\";
        const string CLIENT_DLL = DLL_FOLDER + "dbd_clnt.dll";
        const string ENCRYPT_DLL = DLL_FOLDER + "dbencrypt64.dll";

        const string ENCRYPTED_DB = "TestDBEncrypted";
        const string PASSWORD = "Id.Like.2.Encrypt_This!NOW!";

        [DllImport(CLIENT_DLL, EntryPoint = "Initialize", CharSet = CharSet.Unicode)]
        public static extern void Initialize(bool skipdlg);

        [DllImport(CLIENT_DLL, EntryPoint = "AddPassword", CharSet = CharSet.Unicode)]
        public static extern void AddPassword(string db, string password);

        //C++
        //void WINAPI Initialize (BOOL skipdlg)
        //void WINAPI AddPassword (const wchar_t * database, const wchar_t * password )

        [DllImport(ENCRYPT_DLL, CharSet = CharSet.Unicode)]
        public static extern int Encrypt(Delegate Func, int a, String[] s);

        static void MyCallback(String msg, int code) {
            Console.WriteLine("Output from DLL: {0} {1}", msg, code);
        }

        static void Main(string[] args) {

            // you must run the program locally on the target server
            // if you can't login with trusted connection, add -U and -P parameters for sql user and sql password

            //String[] param = { "MyProc", "-S", ".\\sql2005", "-p", "CoolPassword111", "-d", "mydatabase" };
            //Callback cb = new Callback(MyCallback);
            //int res = Encrypt(cb, param.Length, param);

            //if (res == 0) {
            //    //well done!
            //}

            var parser = new FluentCommandLineParser();
            string connectionString = null;

            parser.Setup<string>('c')
                .Callback(value => connectionString = value);

            parser.Parse(args);

            try {
                var skipDialog = true;

                // DbDefence MAGIC!!

                Initialize(skipDialog);
                AddPassword(ENCRYPTED_DB, PASSWORD);

                // END DbDefence MAGIC!!

                ITestDB context = connectionString == null ? new TestDB() : new TestDB(connectionString);

                foreach (var contact in context.Contacts.ToList()) {
                    Console.WriteLine($"{contact.FirstName}, {contact.LastName}");
                }
            } catch (Exception ex) {
                Console.WriteLine(ex.ToString());

                if (ex.InnerException != null) {
                    Console.WriteLine(ex.InnerException.Message);
                }
            }

            Console.WriteLine("Press [Enter]");
            Console.ReadKey();
        }
    }
}
