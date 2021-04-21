using DBDefense.Models;
using System.Data.Entity;
using System.Linq;

namespace DBDefense.Database {
    public class TestDB : DbContext, ITestDB {

        public DbSet<Contact> ContactTable { get; set; }

        public TestDB(string connectionStringName = "DefaultConnection") : base(connectionStringName) { }

        public IQueryable<Contact> Contacts {
            get {
                return ContactTable;
            }
        }

        public void AddContact(Contact row) {
            ContactTable.Add(row);
        }
    }
}