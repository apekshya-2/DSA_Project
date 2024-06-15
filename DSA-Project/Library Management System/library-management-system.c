#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Define the structures
struct book {
    int id;
    char bookName[50];
    char authorName[50];
    char date[12];
};

struct student {
    int id;
    char sName[50];
    char sClass[50];
    int sRoll;
    char bookName[50];
    char date[12];
};

// Declare file pointers
FILE *fp;
FILE *ft;

// Function declarations
void addBook();
void viewBookList();
void removeBook();
void issueBook();
void viewIssueBookList();

// Main function
int main() {
    int ch;
    while (1) {
        system("cls");
        printf("<== Library Management System ==>\n");
        printf("1. Add book\n");
        printf("2. View book list\n");
        printf("3. Remove book\n");
        printf("4. Issue book\n");
        printf("5. View issued book list\n");
        printf("6. Exit\n\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1:
                addBook();
                break;
            case 2:
                viewBookList();
                break;
            case 3:
                removeBook();
                break;
            case 4:
                issueBook();
                break;
            case 5:
                viewIssueBookList();
                break;
            case 6:
                exit(0);
                break;
            default:
                printf("Invalid choice..\n\n");
        }
        printf("\n\nPress any key to continue...");
        getch();
    }
    return 0;
}

// Function to add a book
void addBook() {
    struct book b;
    char mydate[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(mydate, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    strcpy(b.date, mydate);
    fp = fopen("books.txt", "ab");
    printf("Enter book id: ");
    scanf("%d", &b.id);
    printf("Enter book name: ");
    fflush(stdin);
    gets(b.bookName);
    printf("Enter author name: ");
    fflush(stdin);
    gets(b.authorName);
    printf("Book added successfully\n");
    fwrite(&b, sizeof(b), 1, fp);
    fclose(fp);
}

// Function to view book list
void viewBookList() {
    struct book b;
    system("cls");
    printf("<== Available Books ==>\n\n");
    printf("%-10s %-30s %-20s %-10s\n\n", "Book id", "Book Name", "Author", "Date");
    fp = fopen("books.txt", "rb");
    while (fread(&b, sizeof(b), 1, fp) == 1) {
        printf("%-10d %-30s %-20s %-10s\n", b.id, b.bookName, b.authorName, b.date);
    }
    fclose(fp);
}

// Function to remove a book
void removeBook() {
    struct book b;
    int id, f = 0;
    system("cls");
    printf("<== Remove Book ==>\n\n");
    printf("Enter id to remove book: ");
    scanf("%d", &id);
    fp = fopen("books.txt", "rb");
    ft = fopen("temp.txt", "wb");
    while (fread(&b, sizeof(b), 1, fp) == 1) {
        if (id == b.id) {
            f = 1;
        } else {
            fwrite(&b, sizeof(b), 1, ft);
        }
    }
    if (f == 1) {
        printf("\n\nBook deleted successfully\n");
    } else {
        printf("\n\nNo book found!\n");
    }
    fclose(fp);
    fclose(ft);
    remove("books.txt");
    rename("temp.txt", "books.txt");
}

// Function to issue a book
void issueBook() {
    struct student s;
    struct book b;
    char mydate[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(mydate, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    strcpy(s.date, mydate);
    int f = 0;
    system("cls");
    printf("<== Issue Books ==>\n\n");
    printf("Enter book id to issue: ");
    scanf("%d", &s.id);
    // Check if we have book of given id
    fp = fopen("books.txt", "rb");
    while (fread(&b, sizeof(b), 1, fp) == 1) {
        if (b.id == s.id) {
            strcpy(s.bookName, b.bookName);
            f = 1;
            break;
        }
    }
    fclose(fp);
    if (f == 0) {
        printf("No book found with this id\n");
        printf("Please try again..\n\n");
        return;
    }
    fp = fopen("issue.txt", "ab");
    printf("Enter student name: ");
    fflush(stdin);
    gets(s.sName);
    printf("Enter student class: ");
    fflush(stdin);
    gets(s.sClass);
    printf("Enter student roll number: ");
    scanf("%d", &s.sRoll);
    printf("Book issued successfully\n");
    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);
}

// Function to view issued book list
void viewIssueBookList() {
    struct student s;
    system("cls");
    printf("<== Issued Book List ==>\n\n");
    printf("%-10s %-30s %-20s %-10s %-30s %-10s\n\n", "S. id", "Name", "Class", "Roll", "Book Name", "Date");
    fp = fopen("issue.txt", "rb");
    while (fread(&s, sizeof(s), 1, fp) == 1) {
        printf("%-10d %-30s %-20s %-10d %-30s %-10s\n", s.id, s.sName, s.sClass, s.sRoll, s.bookName, s.date);
    }
    fclose(fp);
}
