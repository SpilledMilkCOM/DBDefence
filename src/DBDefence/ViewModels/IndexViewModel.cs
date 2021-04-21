using DBDefense.Models;
using System.Collections.Generic;

namespace DBDefense.ViewModels {
    public class IndexViewModel {
        public IList<Contact> Contacts { get; set; }
        public IList<Contact> ContactsEncrypted { get; set; }
    }
}