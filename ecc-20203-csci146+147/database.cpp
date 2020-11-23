const int MAX_MARTIANS = 100;

struct Martian {
    std::string fname_;
    std::string lname_;
    std::string SSN_;
    Martian(std::string fn, std::string ln, std::string ssn)
        : fname_(fn), lname_(ln), SSN_(ssn) { }

    // you may add other things to the structure	
};

enum class Criteria { first, last, ssn };

class MartianDatabase {
public:
    // creates a new empty Martian Database initialized with the
    // contents of filename.
    MartianDatabase(std::istream& infile);
    
    // add item m to database, return true if successfully added.
    bool addMartian(const Martian &m);
    
    // delete item with the ssn in database, return true if successfully 
    // deleted.
    bool deleteMartian(std::string ssn);
    
    // return true if the database does not contain any items, false
    // otherwise.
    bool isEmpty();
    
    // return true if the database is at its maximum storage, false
    // otherwise.
    bool isFull();    
    
    // prints the list of Martians, sorted by last name, sorted
    // by first name and by MSSN.
    void printMartians(Criteria type);

    // deletes all the dynamically created memory
    ~MartianDatabase();
private:
    Martian* m_unsorted[MAX_MARTIANS];
    Martian* m_fname[MAX_MARTIANS];
    Martian* m_lname[MAX_MARTIANS];
    Martian* m_ssn[MAX_MARTIANS];

    // you may add other private members to the class
};
