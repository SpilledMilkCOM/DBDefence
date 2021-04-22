using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace DBDefense.Models {
    [Table("Contact")]
    public class Contact {

        [Key]
        public virtual int Id { get; set; }

        [Required]      // NOT NULL
        [StringLength(128)]
        [Display(Name = "First Name")]
        public virtual string FirstName { get; set; }

        [Required]      // NOT NULL
        [StringLength(128)]
        [Display(Name = "Last Name")]
        public virtual string LastName { get; set; }

        [Required]      // NOT NULL
        [StringLength(64)]
        [Display(Name = "Password")]
        public virtual string Password { get; set; }

        [StringLength(128)]
        [Display(Name = "E-Mail")]
        public virtual string Email { get; set; }

        [StringLength(128)]
        [Display(Name = "Phone")]
        public virtual string Phone { get; set; }
    }
}