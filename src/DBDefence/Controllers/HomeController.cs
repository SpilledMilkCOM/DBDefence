using DBDefense.Database;
using DBDefense.Models;
using DBDefense.ViewModels;
using System.Collections.Generic;
using System.Linq;
using System.Web.Mvc;

namespace DBDefense.Controllers {
    public class HomeController : Controller {

        private ITestDB _data = null;
        private ITestDB _dataEncrypted = null;

        public HomeController() : this(new TestDB(), new TestDB("EncryptedConnection")) { }

        public HomeController(ITestDB dataSource, ITestDB dataSourceEncrypted) {
            _data = dataSource;
            _dataEncrypted = dataSourceEncrypted;
        }

        public ActionResult Index() {
            var viewModel = new IndexViewModel();

            viewModel.Contacts = (_data.Contacts != null) ? _data.Contacts.ToList() : new List<Contact>();

            return View(viewModel);
        }

        public ActionResult Encrypted() {
            var viewModel = new IndexViewModel();

            viewModel.ContactsEncrypted = (_dataEncrypted.Contacts != null) ? _dataEncrypted.Contacts.ToList() : new List<Contact>();

            return View(viewModel);
        }

        public ActionResult About() {
            ViewBag.Message = "Your application description page.";

            return View();
        }

        public ActionResult Contact() {
            ViewBag.Message = "Your contact page.";

            return View();
        }
    }
}