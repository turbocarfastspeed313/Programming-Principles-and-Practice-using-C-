#include "Patron.h"
#include "Book.h"
#include <vector>
#include "Exception.h"

namespace Library_f
{
    namespace Transaction
    {
        struct Trasnsaction
        {
            Book::Book book;
            Patron::Patron patron;
            Chrono::Date date;
        };

    } // namespace Transaction

    class Library
    {
    public:
        void add_book(Book::Book b);
        void add_patron(Patron::Patron p);
        void check_out(std::string ISBN);
        bool duplicate_ISBN(std::string ISBN);

        Patron::Patron &patron(std::string name);
        Book::Book &book(std::string ISBN);

        //perhaps add functions to print the vector, get a book and a patron from the book etc.
        //Won't waste time on this because it can be implemented quite easily
        //NOTE : By using vectors as private members, you restrict yourself by relying more member functions than on helper functions

    private:
        std::vector<Book::Book> books;
        std::vector<Patron::Patron> patrons;
    };
        

} // namespace Library_f

static Library_f::Library lib;
static std::vector<Library_f::Transaction::Trasnsaction> transactions;