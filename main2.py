"""
Employee Management System
"""
def ask_user(all_employees):
  choice = "0"
  while choice not in ['1', '2', '3', '4', '5', '6', '7']:
    print("There are currently {l} employees in the system.".format(l = len(all_employees)))
    choice = input("Would you like to: \n1) Enter a new user or \n2) Display all users information\n3) Search for user by SSN\n4) Update a user\n5) Export data\n6) Import data\n7) Exit: ")
  return choice

def take_employee_data():
  employee = {}
  employee['employeeName'] = input("Full name: ")
  employee['employeeSSN_last4'] = input("Last 4 of SSN:" )
  employee['employeePhone'] = input("Phone Number (###)###-#### format: ")
  employee['employeeEmail'] = input("Email: ")
  employee['employeeSalary'] = int(input("salary: "))
  return employee

def print_employee_data(all_employees):
  print(" ")
  for employee in all_employees:
    show_basic_info(employee)
  print(" ")

def show_basic_info(employee):
  num_spaces = 62
  indent = 5
  print_title(num_spaces, employee['employeeName'])
  print_attribute(indent, "SSN:", employee['employeeSSN_last4'])
  print_attribute(indent, "Phone:", employee['employeePhone'])
  print_attribute(indent, "Email:", employee['employeeEmail'])
  print_attribute(indent, "Salary: $", str(employee['employeeSalary']))
  print_footer(num_spaces)
  
def print_title(num_spaces, employeeName):
  tabs = (num_spaces - 2 - len(employeeName)) // 2
  print(tabs * "-", end = '')
  print(" " + employeeName + " ", end = '') 
  print(tabs * "-")
    
def print_attribute(indent, attribute_name, attribute):
  for i in range(0, indent):
    print(" ", end = '')
  print(attribute_name + "" + attribute)
  
def print_footer(num_spaces):
  print(num_spaces * "-")
  print()
  
def search_employee_ssn(all_employees):
  ssn = get_ssn()
  index = get_employee_index(all_employees, ssn)
  if index != -1 :
    show_basic_info(all_employees[index])
  else:
    print("\nEmployee with SSN: %s not found.\n" % ssn)
  return index

def get_ssn():
  ssn = input("Please enter the employee's ssn: ")
  return ssn

def get_employee_index(all_employees, ssn):
  index = -1
  for i, employee in enumerate(all_employees):
    if ssn in employee.values():
      index = i
  return index
  
def refresh_employee(all_employees):
  employee_index = search_employee_ssn(all_employees)
  if employee_index != -1 :
    print("\nEditing employee with SSN {ssn}:".format(ssn = all_employees[employee_index]['employeeSSN_last4']))
    all_employees[employee_index] = take_employee_data()
    
def export_employee_data(all_employees):
  print("\nExporting Employees to employee_data.csv...")
  with open('employee_data.csv', 'w') as file:
    for employee in all_employees:
      line = ""
      for k, v in employee.items():
        line += "{value},".format(value = v)
      file.write(line[:-1]) # writes the line minus the last ','
      file.write('\n')
  print("Exported {n} employees.\n".format(n = len(all_employees)))

def import_employee_data():
  print("\nImporting employees...")
  employees = []
  with open('employee_data.csv', 'r') as file:
    employees_data = file.readlines()
    for employee_data in employees_data:
      employee_data = employee_data.split(',')
      employee = {}
      employee['employeeName'] = employee_data[0]
      employee['employeeSSN_last4'] = employee_data[1]
      employee['employeePhone'] = employee_data[2]
      employee['employeeEmail'] = employee_data[3]
      employee['employeeSalary'] = int(employee_data[4])
      employees.append(employee)
  print("Employees imported.\n")
  return employees

# Variables
all_employees = []
choice = "0"

while choice != "7":
  choice = ask_user(all_employees)
  if choice == '1':
    all_employees.append(take_employee_data())
  elif choice == '2':
    print_employee_data(all_employees)
  elif choice =='3':
    search_employee_ssn(all_employees)
  elif choice == '4':
    refresh_employee(all_employees)
  elif choice == '5':
    export_employee_data(all_employees)
  elif choice == '6':
    all_employees += import_employee_data()
  
print("bye.")
