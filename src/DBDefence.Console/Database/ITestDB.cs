using DBDefense.Models;
using System.Linq;

namespace DBDefense.Database {
    public interface ITestDB {
        IQueryable<Contact> Contacts { get; }

        void AddContact(Contact row);
    }
}