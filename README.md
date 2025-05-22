# 🚍 Transport Management System

## 📄 About the Project

A C-based transport management system that uses linked lists to organize passengers and buses based on destination and timing. It features dynamic assignment, unmatched handling, and operations like adding, deleting, and printing structured data.


## 🧠 Features

- Load bus and passenger information from files.
- Automatically assign passengers to matching buses.
- Maintain unmatched passengers in a separate list.
- Add new passengers dynamically.
- Delete individual passengers or entire buses.
- Print all bus and passenger info with detailed summaries.


## 📂 How It Works

The system is built using three linked lists:
- **Bus List** – Stores bus info like number, date, time, origin, destination, price, capacity.
- **Passenger List** – Stores passenger ID, date, time, origin, and destination.
- **Unmatched List** – Temporarily holds passengers who couldn't be assigned.

Assignment is based on:
- Same **date**.
- Same **time**.
- Same **origin & destination**.
- Bus capacity availability.


## 🖥️ Menu Options

1. Load bus data.  
2. Load passenger data.
3. Assign passengers to buses. 
4. Print bus info with passengers.  
5. Print unmatched passengers. 
6. Add new passenger. 
7. Delete passenger.  
8. Delete bus.  
9. Exit.  
