# Hostel Accommodation Management System

A C++ program for managing hostel accommodation using MySQL and Object-Oriented Programming principles. This system allows users to reserve beds and ensures efficient management of available resources, including storing student names and assigning them a hostel.

## Features
- **Database Integration:** Connects to a MySQL database for efficient data storage and retrieval.
- **Bed Reservation:** Allows users to reserve a bed in a hostel if available.
- **Student Management:** Saves the student's name and the hostel assigned during reservation.
- **Dynamic Bed Management:** Updates the available bed count dynamically after each reservation.
- **Error Handling:** Comprehensive error handling for database connection and query execution.
- **User-Friendly Interface:** Command-line interface for smooth user interaction.

---

## Prerequisites
1. **C++ Compiler:** GCC or any modern C++ compiler.
2. **MySQL Server:** Installed and running on your system.
3. **MySQL Connector for C++:** Required to integrate MySQL with your C++ program.

---

## Database Setup
1. Create the database and tables using the following SQL commands:
    ```sql
    CREATE DATABASE hostel_management;

    USE hostel_management;

    CREATE TABLE hostel (
        id INT AUTO_INCREMENT PRIMARY KEY,
        name VARCHAR(50) NOT NULL,
        total_beds INT NOT NULL,
        available_beds INT NOT NULL
    );

    CREATE TABLE student (
        id INT AUTO_INCREMENT PRIMARY KEY,
        name VARCHAR(50) NOT NULL,
        hostel_id INT NOT NULL,
        FOREIGN KEY (hostel_id) REFERENCES hostel(id)
    );

    INSERT INTO hostel (name, total_beds, available_beds) VALUES 
    ('Hostel A', 100, 100),
    ('Hostel B', 50, 50),
    ('Hostel C', 200, 200);
    ```
2. Update the database credentials in the C++ code:
    ```cpp
    Hostel hostel("localhost", "root", "password", "hostel_management");
    ```

---

## Installation and Usage

### Step 1: Clone the Repository
```bash
git clone https://github.com/your-username/hostel-accommodation-system.git
cd hostel-accommodation-system
 ```
### Step 2: Compile the Code
Use the following command to compile the program with MySQL Connector:
 ```bash
g++ hostel_system.cpp -o hostel_system -lmysqlclient
 ```
###Step 3: Run the Program
 ```bash
./hostel_system
 ```

###Dependencies
MySQL Server
MySQL Connector for C++
C++ Compiler











