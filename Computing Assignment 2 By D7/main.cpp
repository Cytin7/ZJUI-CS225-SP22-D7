// Include required libraries
#include <fstream>
#include <cstdlib>
// Include all head files
#include "time_functions.h"
#include "IO_functions.h"
#include "Record.h"
#include "str_funcions.h"
#include "node_functions.h"
#include "ListNode.h"
#include "RegNode.h"
#include "FibNode.h"
#include "FibHeap.h"
#include "HosNode.h"
#include "withdraw.h"
#include "newmodify.h"
#include "hashmap.h"
#include "BTree.h"
#include "BPlusTree.h"

using namespace std;

// Set number of registries
#define registry_number 7
#define hospital_number 3
#define HALF_DAY 43200

// global variables
const int reg_num = registry_number;
const int hos_num = hospital_number;
int main(){
    system("chcp 65001");
    // Space for declaring necessary variables and objects
    // program time step
    //const time_t HALF_DAY = 43200;
    // current time for system simulation
    time_t current_time = time(nullptr);

    // Set rand() seed
    srand((unsigned)current_time);

    // hash map
    hashmap<int,Record*>* hash_map = new hashmap<int,Record*>;

    // Create file input streams
    fstream reg_file[registry_number] = {};
    // Create structure objects
    RegNode registries;
    registries.setDummy();
    char tmp[256];
    for (int i = 0; i < registry_number; i++) {
        // C:\Users\Jiadong Hong\Desktop\ZJUI-CS225-SP22-D7\Computing Assignment 2 By D7
        reg_file[i].open("./Data/Data" + to_string(i + 1) + ".csv", ios::in);
        reg_file[i].getline(tmp, 256, '\n');  //Remove csv title
        RegNode* new_node = new RegNode;
        (*new_node).setData(i);// &reg_file[i]);
        registries.append(new_node);
    }
    HosNode hospitals;
    hospitals.setDummy();
    for (int i = 0; i < hospital_number; i++) {
        HosNode* new_node = new HosNode;
        (*new_node).setData(i);
        hospitals.append(new_node);
    }
    // center database structures
    ListNode* medium_risk_list[3];
    ListNode* withdraw_list[3];
    FibHeap* main_heap[3];
    FibHeap* ddl_heap[3];
    FibHeap* high_risk_heap[3];
    for (int i = 0; i < 3; i++) {
        (medium_risk_list[i]) = new ListNode; // (*ListNode + i) = ListNode*
        (medium_risk_list[i])->setDummy();
        (withdraw_list[i]) = new ListNode;
        (withdraw_list[i])->setDummy();
        main_heap[i] = new FibHeap(1);
        ddl_heap[i] = new FibHeap(2);
        high_risk_heap[i] = new FibHeap(3);
    }
    int max_id=0;

    // For menu key value
    int menu_key = 0;
    int submenu_key = 0;
    // data needed for report
    int week_reg = 0, week_treated = 0, month_reg = 0, month_treated = 0;
    // Start program
    print_welcome();
// Major loop for operation and time step in
    while (true)
    {
        // print the main menu and get operation key
        menu_key = menu_msg(current_time);
        switch (menu_key)
        {
            /*case 6:
            {
                HosNode* ptr = &hospitals;
                for (int i = 0; i < hospital_number; i++){
                    ptr = ptr->getForward();
                    ptr->printAllRecords();
                }
                continue;
            }*/
            // Modify Regisries
            case 2:
            {
                cin.clear();   // clear the error of wrong data type
                cin.ignore();  // clear the content of wrong data
                submenu_key = registry_msg();
                switch (submenu_key)
                {
                    case 1:
                    {
                        show_registries(&registries);
                        cout << "Input the index of registry to modify mininum registrants per day." << endl;
                        int index = input_msg();
                        if (index < 0 || index >= registry_number) {
                            cout << "Registry does not exist." << endl;
                            break;
                        }
                        RegNode* node = &registries;
                        for (int i = 0; i <= index; i++) {
                            node = (*node).getForward();
                        }
                        cout << "Input the new mininum registrants per day:" << endl;
                        int min = input_msg();
                        if (min < 0) {
                            cout << "Registant number cannot be negative." << endl;
                            break;
                        }
                        else if (min > (*node).getMax()) {
                            (*node).setMin((*node).getMax());
                            (*node).setMax(min);
                        }
                        else {
                            (*node).setMin(min);
                        }
                        break;
                    }
                    case 2:
                    {
                        show_registries(&registries);
                        cout << "Input the index of registry to modify maxinum registrants per day." << endl;
                        int index = input_msg();
                        if (index < 0 || index >= registry_number) {
                            cout << "Registry does not exist." << endl;
                            break;
                        }
                        RegNode* node = &registries;
                        for (int i = 0; i <= index; i++) {
                            node = (*node).getForward();
                        }
                        cout << "Input the new maxinum registrants per day:" << endl;
                        int cap = input_msg();
                        if (cap < 0) {
                            cout << "Registant number cannot be negative." << endl;
                            break;
                        }
                        else if (cap < (*node).getMin()) {
                            (*node).setMax((*node).getMin());
                            (*node).setMin(cap);
                        }
                        else {
                            (*node).setMax(cap);
                        }
                        break;
                    }
                    case 3:
                    {
                        show_registries(&registries);
                        break;
                    }
                    case 9:
                        break;
                    default:
                        cout << "Error: Operation code not found. Please Try again" << endl;
                        break;
                }
                break;
            }
                // Modify Hospitals
            case 3:
            {
                cin.clear();   // clear the error of wrong data type
                cin.ignore();  // clear the content of wrong data
                submenu_key = hospital_msg();
                switch (submenu_key)
                {
                    case 1: {
                        show_hospitals(&hospitals);
                        cout << "Input the hospital that need modify capacity";
                        int index = input_msg();
                        if (index < 0 || index >= hospital_number) {
                            cout << "Hospital does not exist." << endl;
                            break;
                        }
                        HosNode *node = &hospitals;
                        for (int i = 0; i <= index; i++) {
                            node = (*node).getForward();
                        }
                        cout << "Input the new capacity per half-day:" << endl;
                        int cap = input_msg();
                        if (cap < 0) {
                            cout << "Capacity number cannot be negative." << endl;
                            break;
                        } else {
                            (*node).setCapacity(cap);
                        }
                        break;
                    }
                    case 2:
                        show_hospitals(&hospitals);
                        break;
                    case 9:
                        break;
                    default:
                        cout << "Error: Operation code not found. Please Try again" << endl;
                        break;
                }
                break;
            }
            case 4:
            {
                cin.clear();   // clear the error of wrong data type
                cin.ignore();  // clear the content of wrong data
                int withdraw_id;         //NEED A INPUT
                cout << "Please input the id number that requires withdraw" << endl;
                withdraw_id = input_msg();
                for (int treat = 0; treat < 3; treat++) {
                    withdraw_operation(withdraw_id, ddl_heap[treat], main_heap[treat], high_risk_heap[treat], withdraw_list[treat], medium_risk_list[treat], current_time);
                }
                break;
            }
            case 5:
            {
                cin.clear();   // clear the error of wrong data type
                cin.ignore();  // clear the content of wrong data
                int modified_id;         //NEED A INPUT
                int information_type;    //NEED A INPUT: 1 for modifying risk, 2 for modifying profession
                int new_information;     //NEED A INPUT
                //print all records
                // input id
                cout << "Please input the id number that requires modification" << endl;
                modified_id = input_msg();
                cout << "Choose the information that requires modify:" << endl;
                cout << " [1] Risk value" << endl;
                cout << " [2] Profession value" << endl;
                information_type = input_msg();
                cout << "Please input the new value" << endl;
                new_information = input_msg();
                for (int treat = 0; treat < 3; treat++) {
                    if (information_type == 1 || information_type == 2) {
                        modify_operation(modified_id,information_type, new_information,
                            ddl_heap[treat], main_heap[treat], medium_risk_list[treat], high_risk_heap[treat], withdraw_list[treat]);
                    }
                }
                break;
            }
            case 6:
            {
                cin.clear();   // clear the error of wrong data type
                cin.ignore();  // clear the content of wrong data
                Record* record;
                cout << strjust("", 223, '=') << endl;
                cout << strjust("",106,' ') << "Record List" << strjust("",106,' ') << endl;
                cout << strjust("", 223, '-') << endl;
                cout << "| " << strjust("ID", 6) << " | " << strjust("Name", 20)
                     << " | " << strjust("Phone Number", 16) << " | " << strjust("WeChat", 12)
                     << " | " << strjust("E-mail Address", 40) << " | " << strjust("Job", 6)
                     << " | " << strjust("Birthday", 16) << " | " << strjust("Risk", 6)
                     << " | " << strjust("Deadline", 16) << " | " << strjust("Type", 5)
                     << " | " << strjust("Address", 32)  << " | " << strjust("Status", 11) << " |" << endl;
                cout << strjust("|", 222, '-') << "|" << endl;
                for (int id = registry_number; id <= max_id; id++){
                    record = hash_map->hashmap<int, Record *>::retrieve(id);
                    if (record != nullptr) {
                        cout << record->recordInfo();
                        cout << endl;
                    }
                }
                cout << strjust("", 223, '=') << endl;
                break;
            }
            case 7:
            {
                cin.clear();   // clear the error of wrong data type
                cin.ignore();  // clear the content of wrong data
                Record* record;
                submenu_key = filter_msg();
                cout << "Please input the value to match" << endl;
                int match_value = input_msg();
                if (submenu_key==0) {
                    record = hash_map->hashmap<int, Record *>::retrieve(match_value);
                    if (record != nullptr) {
                        cout << record->recordInfo() << endl;
                    }
                    break;
                }
                cout << strjust("", 223, '=') << endl;
                cout << strjust("",106,' ') << "Record List" << strjust("",106,' ') << endl;
                cout << strjust("", 223, '-') << endl;
                cout << "| " << strjust("ID", 6) << " | " << strjust("Name", 20)
                     << " | " << strjust("Phone Number", 16) << " | " << strjust("WeChat", 12)
                     << " | " << strjust("E-mail Address", 40) << " | " << strjust("Job", 6)
                     << " | " << strjust("Birthday", 16) << " | " << strjust("Risk", 6)
                     << " | " << strjust("Deadline", 16) << " | " << strjust("Type", 5)
                     << " | " << strjust("Address", 32)  << " | " << strjust("Status", 11) << " |" << endl;
                cout << strjust("|", 222, '-') << "|" << endl;
                for (int id = registry_number; id <= max_id; id++) {
                    record = hash_map->hashmap<int, Record *>::retrieve(id);
                    if (record == nullptr) {
                        continue;
                    }
                    switch (submenu_key) {
                        case 1: {
                            if (record->age == match_value)
                                cout << record->recordInfo() << endl;
                            break;
                        }
                        case 2: {
                            if (record->age_group == match_value)
                                cout << record->recordInfo() << endl;
                            break;
                        }
                        case 3: {
                            if (record->profession == match_value)
                                cout << record->recordInfo() << endl;
                            break;
                        }
                        case 4: {
                            if (record->risk == match_value)
                                cout << record->recordInfo() << endl;
                            break;
                        }
                        case 5: {
                            if (record->registry == match_value)
                                cout << record->recordInfo() << endl;
                            break;
                        }
                        case 6: {
                            if (record->hospital == match_value)
                                cout << record->recordInfo() << endl;
                            break;
                        }
                        case 7: {
                            if (record->treatment == match_value)
                                cout << record->recordInfo() << endl;
                            break;
                        }
                        case 8: {
                            if (record->status == match_value)
                                cout << record->recordInfo() << endl;
                            break;
                        }

                    }
                }
                cout << strjust("", 223, '=') << endl;
                break;
            }
                // Exit the program
            case 9:
            {
                // Quit the program
                cout << "Closing the program..." << endl << endl;
                for (int i = 0; i < registry_number; i++) {
                    reg_file[i].close();
                }
                print_goodbye();
                return 0;
            }
                // Main loop -> half day simulation
            case 1:
            {
                // Time step forward for half day
                current_time += HALF_DAY;
                // Read files
                char tmp[256] = {};
                string data;
                RegNode* reg = registries.getForward();
                // Read file data for registrants record data
                // For real simulation, every halfday, the regitory take in random number people, within a set range
                // and the filestream always hold in the main program, read line by line each halfday
                // all value are stored in the link node

                for (int i = 0; i < registry_number; i++) {
                    int read_num = (*reg).getMax();
                    if (reg_file[i].eof()) {
                        continue;
                    }
                    for (int j = 0; j < read_num; j++) {
                        reg_file[i].getline(tmp, 256, '\n');
                        data = tmp;
                        if (reg_file[i].eof() || data == "") {
                            break;
                        } else {
                            ListNode *node = new ListNode;
                            (*node).setRecordwithData(data, i, current_time);
                            (*reg).getList()->append(node);
                            (*node).getRecord()->status = 1;
                            hash_map->add(node->getRecord()->id,node->getRecord());
                            if (node->getRecord()->id>max_id)
                                max_id=node->getRecord()->id;
                            week_reg++;
                            month_reg++;
                        }
                    }
                    // Print the message.
                    (*reg).printAllRecords();
                    reg = (*reg).getForward();
                }
                // send data to main heap
                {
                    reg = registries.getForward();
                    ListNode* ptr;
                    for (int i = 0; i < registry_number; i++) {
                        ptr = (*(*(*reg).getList()).getOld()).getForward();
                        while (!(*ptr).getDummyBool()) {
                            // judge the risk level.
                            FibNode* fibn, * fibc;
                            ListNode* listn;
                            int treat = (*(*ptr).getRecord()).getRecordTreatment();
                            switch ((*(*ptr).getRecord()).getRecordRisk())
                            {
                                case 0:
                                case 1:
                                    fibn = (*ptr).toFibNode(1);
                                    fibc = (*ptr).toFibNode(2);
                                    (*main_heap[treat]).insert(fibn, major_prior);
                                    if ((*(*ptr).getRecord()).getRecordDDLBool()) {
                                        Record* rcd = fibn->record;
                                        fibc->record = rcd;
                                        fibc->calcKey();
                                        (*ddl_heap[treat]).insert(fibc, ddl_prior);
                                    }
                                    break;
                                case 2:
                                    // medium risk
                                    listn = (*ptr).copy();
                                    (*medium_risk_list[treat]).insert(listn);
                                    break;
                                case 3:
                                    // high risk
                                    fibn = (*ptr).toFibNode(1);
                                    (*high_risk_heap[treat]).insert(fibn, major_prior);
                                    break;
                                default:
                                    break;
                            }
                            ptr = (*ptr).getForward();
                        }
                        // set old to new value;
                        (*(*reg).getList()).setOld(((*reg).getList()->getBackward()));
                        reg = (*reg).getForward();
                    }
                }
                // transport eligible record in withdraw list to main heap
                for (int treat = 0; treat < 3; treat++) {
                    while (!(*(*withdraw_list[treat]).getBackward()).getDummyBool())
                    {
                        FibNode* fibn, * fibc;
                        ListNode* listn = (*withdraw_list[treat]).getBackward();
                        Record* record = (*listn).getRecord();
                        if (current_time >= ((*record).getRecordRegisterTime() + 14 * 2 * HALF_DAY)) {
                            listn = (*withdraw_list[treat]).drop();
                            listn->getRecord()->status = 1;
                            (*record).setRecordRegisterTime(current_time);
                            switch ((*record).getRecordRisk())
                            {
                            case 0:
                            case 1:
                                fibn = (*listn).toFibNode(1);
                                fibc = (*listn).toFibNode(2);
                                (*main_heap[treat]).insert(fibn, major_prior);
                                if ((*record).getRecordDDLBool()) {
                                    // fibc = (*fibn).copy();
                                    fibc->record = fibn->record;
                                    fibc->calcKey();
                                    (*ddl_heap[treat]).insert(fibc, ddl_prior);
                                }
                                break;
                            case 2:
                                (*medium_risk_list[treat]).insert(listn);
                                break;
                            case 3:
                                fibn = (*listn).toFibNode(1);
                                (*high_risk_heap[treat]).insert(fibn, major_prior);
                                break;
                            default:
                                break;
                            }
                        }
                        else {
                            break;
                        }
                    }
                    // transport eligible record in medium risk list to main heap
                    while (!(*(*medium_risk_list[treat]).getBackward()).getDummyBool())
                    {
                        FibNode* fibn, * fibc;
                        ListNode* listn = (*medium_risk_list[treat]).getBackward();
                        Record* record = (*listn).getRecord();
                        time_t time = (*record).getRecordRegisterTime();
                        if (current_time >= ((*record).getRecordRegisterTime() + 30 * 2 * HALF_DAY)) {
                            listn = (*medium_risk_list[treat]).drop();
                            fibn = (*listn).toFibNode(1);
                            fibc = (*listn).toFibNode(2);
                            (*main_heap[treat]).insert(fibn, major_prior);
                            if ((*record).getRecordDDLBool()) {
                                fibc->record = fibn->record;
                                fibc->calcKey();
                                (*ddl_heap[treat]).insert(fibc, ddl_prior);
                            }
                        }
                        else {
                            break;
                        }
                    }
                    cout << "The number in the heap is " << main_heap[treat]->getNumitems() << "." << endl;
                    cout<<"Treat value is "<<treat<<endl;
                    // assign patient to hospitals
                    {
                        HosNode* hos = hospitals.getForward();
                        ListNode* listn;
                        int cap, counter;
                        for (int i = 0; i < hospital_number; i++)
                        {
                            cap = (*hos).getCapacity();
                            cout << "NO." << i + 1 << " Hospital have remaining capacity of " << cap << "." << endl;
                            counter = 0;
                            while ((counter < cap) && (0 != (*ddl_heap[treat]).getNumitems())) {
                                if ((current_time + 2 * HALF_DAY) <=
                                    (*(*(*ddl_heap[treat]).getMin()).getRecord()).getRecordDeadline()) {
                                    FibNode *fibn;
                                    fibn = (*ddl_heap[treat]).pop_min(ddl_prior);
                                    listn = toListNode(fibn);
                                    (*(*hos).getList()).append(listn);
                                    listn->getRecord()->status = 2;
                                    listn->getRecord()->hospital = i+1;
                                    int id = (*(*listn).getRecord()).getRecordID();
                                    cout << "\tThe No." << id << " has just pop of the ddl heap and got rescued."
                                         << endl;
                                    (*main_heap[treat]).delete_node(id, major_prior);
                                    counter++;
                                    delete fibn;
                                    //Add this part
                                    week_treated++;
                                    month_treated++;
                                } else {
                                    cout<<"DDL Heap not empty"<<endl;
                                    break;
                                }
                            }
                            cout << "The ddl heap pop is over." << endl;
                            while ((counter < cap) && (0 != (*main_heap[treat]).getNumitems())) {
                                FibNode* fibn;
                                fibn = &(*(*main_heap[treat]).pop_min(major_prior));
                                listn = toListNode(fibn);
                                (*(*hos).getList()).append(listn);
                                listn->getRecord()->status = 2;
                                int id = (*(*listn).getRecord()).getRecordID();
                                cout << "\tThe No." << id << " has just pop of the main heap and got rescued."
                                     << endl;
                                if ((*(*listn).getRecord()).getRecordDDLBool()) {
                                    (*ddl_heap[treat]).delete_node((*(*listn).getRecord()).getRecordID(), ddl_prior);
                                }
                                counter++;
                                delete fibn;
                                //Add this part
                                week_treated++;
                                month_treated++;
                            }
                            if(main_heap[treat]->getNumitems()<=0){
                                cout<<"Main heap is empty";
                            }
                            while ((counter < cap) && (0 != (*high_risk_heap[treat]).getNumitems())) {
                                FibNode* fibn;
                                fibn = &(*(*high_risk_heap[treat]).pop_min(major_prior));
                                listn = toListNode(fibn);
                                (*(*hos).getList()).append(listn);
                                listn->getRecord()->status = 2;
                                int id = (*(*listn).getRecord()).getRecordID();
                                cout << "\tThe No." << id << " has just pop of the highrisk heap and got rescued."
                                     << endl;
                                counter++;
                                delete fibn;
                                //Add this part
                                week_treated++;
                                month_treated++;
                            }
                            if (counter < cap) {
                                cout << "there is still some remaining capacity among hospitals." << endl;
                                cout << "The number in the main heap/queueing is " << main_heap[treat]->getNumitems() << "." << endl;
                            }
                            hos = (*hos).getForward();
                        }
                    }
                }
                for(int treat=0;treat<3;treat++){
                    cout<<"This is main heap number"<<treat<<endl;
                    main_heap[treat]->print();
                }
                {
                    // week report
                    tm *time_tm = localtime(&current_time);
                    if ((*time_tm).tm_wday == 0 && (*time_tm).tm_hour < 12) {
                        fstream week_file;
                        week_file.open("./week_report/" + repstr(date_str(current_time), "., ", '_') + ".md",
                                       ios::out);
                        week_file << "# Week " + date_str(current_time) + " Report" << endl;

                        week_file << "## Overall information" << endl;
                        week_file << "Patient registed: **" << hash_map->numitems << "**" << endl;
                        week_file << "Patient registed this week: **" << week_reg << "**" << endl;
                        week_file << "Patient treated this week: **" << week_treated << "**" << endl;
                        week_reg = 0;
                        week_treated = 0;
                        week_file << "Patient with no or low risk waiting: **"
                                  << main_heap[0]->getNumitems() + main_heap[1]->getNumitems() +
                                     main_heap[2]->getNumitems() << "**" << endl;
                        week_file << "Patient with medium risk waiting: **"
                                  << medium_risk_list[0]->getLength() + medium_risk_list[1]->getLength() +
                                     medium_risk_list[2]->getLength() << "**" << endl;
                        week_file << "Patient with high risk waiting: **"
                                  << high_risk_heap[0]->getNumitems() + high_risk_heap[1]->getNumitems() +
                                     high_risk_heap[2]->getNumitems() << "**" << endl;

                        Record *record;
                        ListNode *listn;
                        RegNode *regn = &registries;
                        HosNode *hosn = &hospitals;
                        week_file << "## Patient registed this week"<<endl;
                        week_file << "| " << "ID" << " | " << "Name" << " | " << "Phone Number" << " | " << "WeChat"
                                  << " | " << "E-mail Address" << " | " << "Job" << " | " << "Birthday" << " | "
                                  << "Risk" << " | " << "Deadline" << " | " << "Type" << " | " << "Address" << " | "
                                  << "Status" << " |" << endl;
                        week_file << "| " << "--- | " << "--- | " << "--- | " << "--- | " << "--- | " << "--- | "
                                  << "--- | " << "--- | " << "--- | " << "--- | " << "--- | " << "--- |" << endl;
                        for (int reg = 0; reg < registry_number; reg++) {
                            regn = regn->getForward();
                            listn = (*regn).getList()->getLastWeek();
                            while (!(listn->getForward()->getDummyBool())) {
                                listn = listn->getForward();
                                record = listn->getRecord();
                                if (record != nullptr) {
                                    week_file << record->recordInfo() << endl;
                                }
                            }
                            (*regn).getList()->setLastWeek((*regn).getList());
                        }
                        week_file << endl;

                        week_file << "## Patient Treated this week"<<endl;
                        week_file << "| " << "ID" << " | " << "Name" << " | " << "Phone Number" << " | " << "WeChat"
                                  << " | " << "E-mail Address" << " | " << "Job" << " | " << "Birthday" << " | "
                                  << "Risk" << " | " << "Deadline" << " | " << "Type" << " | " << "Address" << " | "
                                  << "Status" << " |" << endl;
                        week_file << "| " << "--- | " << "--- | " << "--- | " << "--- | " << "--- | " << "--- | "
                                  << "--- | " << "--- | " << "--- | " << "--- | " << "--- | " << "--- |" << endl;
                        for (int hos = 0; hos < hospital_number; hos++) {
                            hosn = hosn->getForward();
                            listn = (*hosn).getList()->getLastWeek();
                            while (!(listn->getForward()->getDummyBool())) {
                                listn = listn->getForward();
                                record = listn->getRecord();
                                if (record != nullptr) {
                                    week_file << record->recordInfo() << endl;
                                }
                            }
                            (*hosn).getList()->setLastWeek((*hosn).getList());

                        }
                        week_file << endl;
                        week_file << "## Patient Waiting to be assigned now"<<endl;
                        week_file << "| " << "ID" << " | " << "Name" << " | " << "Phone Number" << " | " << "WeChat"
                                  << " | " << "E-mail Address" << " | " << "Job" << " | " << "Birthday" << " | "
                                  << "Risk" << " | " << "Deadline" << " | " << "Type" << " | " << "Address" << " | "
                                  << "Status" << " |" << endl;
                        week_file << "| " << "--- | " << "--- | " << "--- | " << "--- | " << "--- | " << "--- | "
                                  << "--- | " << "--- | " << "--- | " << "--- | " << "--- | " << "--- |" << endl;
                        for (int id = registry_number; id <= max_id; id++) {
                            record = hash_map->hashmap<int, Record *>::retrieve(id);
                            if (record != nullptr && record->status == 1)
                                week_file << record->recordInfo() << endl;
                        }
                    }

                    // month report
                    if ((*time_tm).tm_mday == 1 && (*time_tm).tm_hour < 12) {
                        fstream month_file;
                        month_file.open("./month_report/" + repstr(date_str(current_time), "., ", '_') + ".md",
                                        ios::out);
                        month_file << "# month " + date_str(current_time) + " Report" << endl;

                        month_file << "## Overall information" << endl;
                        month_file << "Patient registed: **" << hash_map->numitems << "**" << endl;
                        month_file << "Patient registed this month: **" << month_reg << "**" << endl;
                        month_file << "Patient treated this month: **" << month_treated << "**" << endl;
                        month_reg = 0;
                        month_treated = 0;
                        month_file << "Patient with no or low risk waiting: **"
                                   << main_heap[0]->getNumitems() + main_heap[1]->getNumitems() +
                                      main_heap[2]->getNumitems() << "**" << endl;
                        month_file << "Patient with medium risk waiting: **"
                                   << medium_risk_list[0]->getLength() + medium_risk_list[1]->getLength() +
                                      medium_risk_list[2]->getLength() << "**" << endl;
                        month_file << "Patient with high risk waiting: **"
                                   << high_risk_heap[0]->getNumitems() + high_risk_heap[1]->getNumitems() +
                                      high_risk_heap[2]->getNumitems() << "**" << endl;

                        Record *record;
                        ListNode *listn;
                        RegNode *regn = &registries;
                        HosNode *hosn = &hospitals;
                        month_file << "## Patient registed this month"<<endl;
                        month_file << "| " << "ID" << " | " << "Name" << " | " << "Phone Number" << " | " << "WeChat"
                                   << " | " << "E-mail Address" << " | " << "Job" << " | " << "Birthday" << " | "
                                   << "Risk" << " | " << "Deadline" << " | " << "Type" << " | " << "Address" << " | "
                                   << "Status" << " |" << endl;
                        month_file << "| " << "--- | " << "--- | " << "--- | " << "--- | " << "--- | " << "--- | "
                                   << "--- | " << "--- | " << "--- | " << "--- | " << "--- | " << "--- |" << endl;
                        for (int reg = 0; reg < registry_number; reg++) {
                            regn = regn->getForward();
                            listn = (*regn).getList()->getLastMonth();
                            while (!(listn->getForward()->getDummyBool())) {
                                listn = listn->getForward();
                                record = listn->getRecord();
                                if (record != nullptr) {
                                    month_file << record->recordInfo() << endl;
                                }
                            }
                            (*regn).getList()->setLastMonth((*regn).getList());
                        }
                        month_file << endl;

                        month_file << "## Patient Treated this month"<<endl;
                        month_file << "| " << "ID" << " | " << "Name" << " | " << "Phone Number" << " | " << "WeChat"
                                   << " | " << "E-mail Address" << " | " << "Job" << " | " << "Birthday" << " | "
                                   << "Risk" << " | " << "Deadline" << " | " << "Type" << " | " << "Address" << " | "
                                   << "Status" << " |" << endl;
                        month_file << "| " << "--- | " << "--- | " << "--- | " << "--- | " << "--- | " << "--- | "
                                   << "--- | " << "--- | " << "--- | " << "--- | " << "--- | " << "--- |" << endl;
                        for (int hos = 0; hos < hospital_number; hos++) {
                            hosn = hosn->getForward();
                            listn = (*hosn).getList()->getLastMonth();
                            while (!(listn->getForward()->getDummyBool())) {
                                listn = listn->getForward();
                                record = listn->getRecord();
                                if (record != nullptr) {
                                    month_file << record->recordInfo() << endl;
                                }
                            }
                            (*hosn).getList()->setLastMonth((*hosn).getList());

                        }
                        month_file << endl;
                        month_file << "## Patient Waiting to be assigned now"<<endl;
                        month_file << "| " << "ID" << " | " << "Name" << " | " << "Phone Number" << " | " << "WeChat"
                                   << " | " << "E-mail Address" << " | " << "Job" << " | " << "Birthday" << " | "
                                   << "Risk" << " | " << "Deadline" << " | " << "Type" << " | " << "Address" << " | "
                                   << "Status" << " |" << endl;
                        month_file << "| " << "--- | " << "--- | " << "--- | " << "--- | " << "--- | " << "--- | "
                                   << "--- | " << "--- | " << "--- | " << "--- | " << "--- | " << "--- |" << endl;
                        for (int id = registry_number; id <= max_id; id++) {
                            record = hash_map->hashmap<int, Record *>::retrieve(id);
                            if (record != nullptr && record->status == 1)
                                month_file << record->recordInfo() << endl;
                        }
                    }
                    break;
                }
            }
            default: {
                cout << "Error: Operation code not found. Please Try again" << endl;
                break;
            }
        }
        menu_key = 0;
        submenu_key = 0;
        cin.clear();   // clear the error of wrong data type
        cin.ignore();  // clear the content of wrong data
    }
}
