#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX 1000
typedef struct node_major node_major; // we need to define it first because in attributes we have node_major
// 1. Define Student structure
typedef struct
{
  int ID;
  char Fname[50];
  char Lname[50];
  int age;
  float grade;
  char major[50];
} Student;

struct node_major // I used a linked list structure to do the Major analytics so the expansion will be O(1)
{
  char major_name[50];
  node_major *ptr_next;
  int count;
};

void Print_student(Student student)
{
  printf("Student ID:%d\n", student.ID);
  printf("Student first name:%s\n", student.Fname);
  printf("Student last name:%s\n", student.Lname);
  printf("Student age:%d\n", student.age);
  printf("Student grade:%.1f\n", student.grade);
  printf("Student major:%s\n", student.major);
  printf("*************************\n");
}

bool Add_Student(Student **array, int *size)
{
  int new_size = sizeof(Student) * (*size + 1);
  Student *temp = realloc(*array, new_size);
  if (temp == NULL)
  {
    return false;
  }
  else
  {
    *array = temp;
    printf("Enter Student ID:");
    scanf("%d", &(*array)[*size].ID);

    printf("Enter Student First name:");
    scanf("%49", (*array)[*size].Fname);

    printf("Enter Student Last name:");
    scanf("%49", (*array)[*size].Lname); // we need to put brackets because the [] has a higher precedence than *

    printf("Enter Student age:");
    scanf("%d", &(*array)[*size].age);

    printf("Enter Student grade:");
    scanf("%f", &(*array)[*size].grade);

    printf("Enter Student major:");
    scanf("%49", (*array)[*size].major);
    *size += 1;
    printf("===STUDENT ADD SUCCESSFULLY==\n");
    return true;
  }
}

void View_All(Student *array, int size)
{
  for (int i = 0; i < size; i++)
  {
    Print_student(array[i]);
  }
}

int Print_menu()
{
  int op;
  printf("Please choose the operation:\n1. Add Student\n2. View All Students\n3. Search Student\n4. Update Student\n5. Delete Student\n6. Show Statistics\n7. Save and Exit\nEnter wished operation number:"); // alt+z for wrap text ;)
  scanf("%d", &op);
  return op;
}

void Search_Student(Student *array, int size)
{
  // first search by what ?
  int choice;
  printf("Search Students by:\n1. ID\n2. Last Name\n3. Major\nPlease enter your choice:");
  scanf("%d", &choice);
  switch (choice)
  {

  case 1:

    int wishedID;
    printf("Please Enter ID:");
    scanf("%d", &wishedID);

    printf("_____________________\n");

    for (int i = 0; i < size; i++)
    {
      if (array[i].ID == wishedID)
      {
        Print_student(array[i]); // assuming that the ID is unique
        return;
      }
    }
    printf("STUDENT NOT FOUND!\n");
    break;

  case 2:
    char wishedL[50];
    printf("Enter Student's Last Name:");
    scanf("%49s", wishedL);
    while (getchar() != '\n')
      ;

    printf("_____________________\n");

    int fL = 0;
    for (int i = 0; i < size; i++)
    {
      if (strcmp(array[i].Lname, wishedL) == 0)
      {
        Print_student(array[i]);
        fL = 1;
      }
    }
    if (fL == 0)
    {
      printf("STUDENT NOT FOUND!\n");
    }

    break;

  case 3:
    char wishedM[50];
    printf("Enter Student's Major:");
    while (getchar() != '\n')
      ;
    fgets(wishedM, sizeof(wishedM), stdin);

    printf("_____________________\n");
    wishedM[strcspn(wishedM, "\n")] = '\0';
    int fM = 0;
    for (int i = 0; i < size; i++)
    {
      // printf("%s ", array[i].major);
      if (strcmp(array[i].major, wishedM) == 0)
      {
        Print_student(array[i]);
        fM = 1;
      }
    }
    if (fM == 0)
    {
      printf("\nSTUDENT NOT FOUND!\n");
    }

    break;
  }
}

void Update_Student(Student *array, int size)
{
  int upID;
  printf("Please enter the student ID:");
  scanf("%d", &upID);
  int wished = 0;
  while (wished < size)
  {
    if (array[wished].ID == upID)
    {
      break;
    }
    wished++;
  }
  if (wished == size)
  {
    printf("STUDENT NOT FOUND!\n");
    return;
  }
  Print_student(array[wished]);
  printf("What to update:\n1. Last Name\n2. First Name\n3. Grade\n4. Age\n5. Major\nYour Choice:");
  int choice;
  scanf("%d", &choice);
  Student *Current = &array[wished];
  switch (choice)
  {
  case 2:
    char Fname[50];
    printf("Enter updated name:");
    scanf("%49", Fname);
    strcpy(Current->Fname, Fname);
    break;
  case 1:
    char Lname[50];
    printf("Enter updated name:");
    scanf("%49", Lname);
    strcpy(Current->Lname, Lname);
    break;

  case 5:
    char major[50];
    printf("Enter updated major:");
    scanf("%49", major);
    strcpy(Current->major, major);
    break;

  case 3:
    int grade;
    printf("Enter updated Grade:");
    scanf("%f", &grade);
    Current->grade = grade;
    break;

  case 4:
    int age;
    printf("Enter updated age:");
    scanf("%d", &age);
    Current->age = age;
    break;
  }
}
void Delete_Student(Student **array, int *size)
{
  int deletedID;
  printf("Enter the Student ID:");
  scanf("%d", &deletedID);
  int deleted = 0; // index of the item we want to delete
  int temp = *size;
  while (deleted < temp)
  {
    if ((*array)[deleted].ID == deletedID)
    {
      break;
    }
    deleted++;
  }
  if (deleted == temp)
  {
    printf("STUDENT NOT FOUND!\n");
    return;
  }
  // we will move the elements by a step to the back overriding the deleted element and we will leave the last element
  for (int i = deleted; i < temp - 1; i++)
  {
    (*array)[i] = (*array)[i + 1];
  }
  int new_size = sizeof(Student) * (temp - 1);
  Student *TempArray = realloc(*array, new_size);
  if (TempArray == NULL)
  {
    printf("Deleting student failed\n");
    return;
  }
  else
  {
    *array = TempArray;
    *size -= 1;
    printf("===STUDENT DELETED SUCCESSFULLY==\n");
  }
}

void Analysis(Student *array, int size)
{
  float sum_age = 0, sum_grade = 0, high_grade = 0, low_grade = 100;

  for (int i = 0; i < size; i++)
  {
    sum_age += (float)array[i].age;
    sum_grade += array[i].grade;
    if (array[i].grade > high_grade)
    {
      high_grade = array[i].grade;
    }
    if (array[i].grade < low_grade)
    {
      low_grade = array[i].grade;
    }
  }
  float avg_age = sum_age / size;
  float avg_grade = sum_grade / size;
  printf("*STATISTICS*\n- Average Grade:%.2f\n- Average Age:%.2f\n- Highest Grade:%.2f\n- Lowest Grade:%.2f\n", avg_grade, avg_age, high_grade, low_grade);
}
/*
1. heap memory (created by malloc and all) don't get freed automatically when exiting the scope but stack memory does
2. we need to use malloc for the new node so they don't get destroyed after exiting the scope of the iteration */
void major_analytics(Student *array, int size)
{
  if (size == 0)
  {
    printf("No students available for major statistics.\n");
    return;
  }
  else
  {
    node_major *head = malloc(sizeof(node_major));
    head->ptr_next = NULL;
    strcpy(head->major_name, array[0].major);
    head->count = 1;
    // node_major *current = &head;

    for (int i = 1; i < size; i++)
    {

      // first check we have this major or not
      node_major *iterate = head;
      node_major *previous = NULL;
      int found = 0;
      while (iterate != NULL) // first look if the major is already in the linked list if so just tweak the count
      {

        if (strcmp(iterate->major_name, array[i].major) == 0)
        {
          iterate->count += 1;
          found = 1;
          break;
        }
        previous = iterate;
        iterate = iterate->ptr_next;
      }
      if (!found) // if iterate is null meaning the major is not in the linked list so we have to add it
      {
        node_major *new_node = malloc(sizeof(node_major));
        new_node->count = 1;
        strcpy(new_node->major_name, array[i].major);
        new_node->ptr_next = NULL;
        previous->ptr_next = new_node;
      }
    }
    node_major *current = head;
    printf("Major Statistics:\n____________\n");
    while (current != NULL)
    {
      node_major *temp = current;
      printf("-Major:%s\n-Student Count:%d\n***************\n", current->major_name, current->count);
      current = current->ptr_next;
      free(temp);
    }
  }
}
int main()
{

  // 2. I/O CSV file

  FILE *ptr;
  ptr = fopen("D:/C/Student_Project/student.csv", "r");
  if (ptr == NULL) // error handling
  {
    printf("Unable to open the file");
  }
  else
  {
    int count_student = 0;

    char buffer[MAX]; // load lines here
    fgets(buffer, MAX, ptr);

    // first we need to get the students number
    while (fgets(buffer, MAX, ptr))
    {
      count_student++;
    }

    Student *student_array = calloc(count_student, sizeof(Student));

    rewind(ptr);
    fgets(buffer, MAX, ptr);
    // load the data to the student array

    char *Token;
    int i = 0; // iterate over the student array
    // load the data into the array
    while (fgets(buffer, MAX, ptr))
    {
      buffer[strcspn(buffer, "\n")] = '\0';

      Token = strtok(buffer, ",");

      int j = 0; // so we can know which part of csv are we
      while (Token != NULL)
      {

        switch (j) // we now are loading each info to its place
        {
        case 0:
          student_array[i].ID = atoi(Token);

          break;
        case 1:
          strcpy(student_array[i].Fname, Token);

          break;
        case 2:
          strcpy(student_array[i].Lname, Token);
          break;
        case 3:
          student_array[i].age = atoi(Token);
          break;
        case 4:
          student_array[i].grade = atof(Token);
          break;
        case 5:
          strcpy(student_array[i].major, Token);
          break;

        default:
          break;
        }
        Token = strtok(NULL, ",");
        j++;
      }
      i++;
    }

    int choice = Print_menu();
    while (choice != 7)
    {
      switch (choice)
      {
      case 1:
        Add_Student(&student_array, &count_student);
        break;
      case 2:
        View_All(student_array, count_student);
        break;
      case 3:
        Search_Student(student_array, count_student);
        break;
      case 4:
        Update_Student(student_array, count_student);
        break;
      case 5:
        Delete_Student(&student_array, &count_student);
        break;
      case 6:
        Analysis(student_array, count_student);
        major_analytics(student_array, count_student);
        break;

      default:
        break;
      }
      printf("Press Enter to continue...");

      getchar();
      choice = Print_menu();
    }

    FILE *save;
    save = fopen("D:/C/Student_Project/student.csv", "w");
    if (save == NULL)
    {
      printf("UNABLE TO SAVE\n");
    }
    else
    {
      fprintf(save, "id,first_name,last_name,age,grade,major\n");
      for (int i = 0; i < count_student; i++)
      {
        Student current_student = student_array[i];
        fprintf(save, "%d,%s,%s,%d,%.2f,%s\n", current_student.ID, current_student.Fname, current_student.Lname, current_student.age, current_student.grade, current_student.major);
      }
      fclose(save);
    }

    free(student_array);
  }

  return 0;
}
