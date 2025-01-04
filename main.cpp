#include <iostream>
#include <mysql/mysql.h>
#include <string>

class Hostel {
private:
    MYSQL *conn;
    MYSQL_ROW row;
    MYSQL_RES *res;

    std::string host, user, password, database;

    void connectToDatabase() {
        conn = mysql_init(0);
        conn = mysql_real_connect(conn, host.c_str(), user.c_str(), password.c_str(), database.c_str(), 3306, NULL, 0);
        if (conn) {
            std::cout << "Connected to the database successfully.\n";
        } else {
            std::cerr << "Database connection failed: " << mysql_error(conn) << "\n";
            exit(1);
        }
    }

    bool checkAvailableBeds(int &hostelId, std::string &hostelName) {
        std::string query = "SELECT id, name, available_beds FROM hostel WHERE available_beds > 0 LIMIT 1;";
        if (mysql_query(conn, query.c_str()) == 0) {
            res = mysql_store_result(conn);
            if (res && (row = mysql_fetch_row(res))) {
                hostelId = std::stoi(row[0]);
                hostelName = row[1];
                mysql_free_result(res);
                return true;
            }
        }
        return false;
    }

    void updateBedCount(int hostelId) {
        std::string query = "UPDATE hostel SET available_beds = available_beds - 1 WHERE id = " + std::to_string(hostelId) + ";";
        mysql_query(conn, query.c_str());
    }

    void saveStudentData(const std::string &studentName, int hostelId) {
        std::string query = "INSERT INTO student (name, hostel_id) VALUES ('" + studentName + "', " + std::to_string(hostelId) + ");";
        if (mysql_query(conn, query.c_str()) != 0) {
            std::cerr << "Failed to save student data: " << mysql_error(conn) << "\n";
        }
    }

public:
    Hostel(const std::string &host, const std::string &user, const std::string &password, const std::string &database)
        : host(host), user(user), password(password), database(database) {
        connectToDatabase();
    }

    ~Hostel() {
        mysql_close(conn);
    }

    void reserveBed() {
        std::string studentName;
        std::cout << "Enter your name: ";
        std::getline(std::cin, studentName);

        int hostelId;
        std::string hostelName;
        if (checkAvailableBeds(hostelId, hostelName)) {
            saveStudentData(studentName, hostelId);
            updateBedCount(hostelId);
            std::cout << "Reservation successful for " << studentName << " in " << hostelName << "!\n";
        } else {
            std::cout << "No beds are currently available.\n";
        }
    }

    void menu() {
        int choice;
        do {
            std::cout << "\nHostel Accommodation System\n";
            std::cout << "1. Reserve Bed\n";
            std::cout << "2. Exit\n";
            std::cout << "Enter your choice: ";
            std::cin >> choice;
            std::cin.ignore(); // To clear the newline character left in the buffer

            switch (choice) {
            case 1:
                reserveBed();
                break;
            case 2:
                std::cout << "Exiting the program.\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 2);
    }
};

int main() {
    Hostel hostel("localhost", "root", "password", "hostel_management");
    hostel.menu();
    return 0;
}
