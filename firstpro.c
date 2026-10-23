#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>  

int analyze_password(char pwd[]) {
    int length = strlen(pwd);
    int Upper = 0, Lower = 0, Digit = 0, Special = 0;
    int types = 0;

    for (int i = 0; i < length; i++) {
        if (pwd[i] >= 'A' && pwd[i] <= 'Z') Upper = 1;
        else if (pwd[i] >= 'a' && pwd[i] <= 'z') Lower = 1;
        else if (pwd[i] >= '0' && pwd[i] <= '9') Digit = 1;
        else Special = 1;
    }

    types = Upper + Lower + Digit + Special;

    if (length >= 8 && Upper && Lower && Digit && Special) { return 3; }
    else if (length >= 8 && types >= 3) { return 2; }
    else if (length >= 6 && types >= 2) { return 1; }
    else return 0;
}

void generate_strong_password(char dest[]) {
    char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*";
    int length = 12;
    int i;
    for (i = 0; i < length; i++) {
        int ind = rand() % (sizeof(charset) - 1);
        dest[i] = charset[ind];
    }
    dest[i] = '\0';
}

void save_to_vault(char acc_name[], char username[], char password[]) {
    FILE *file = fopen("vault_data.txt", "a");
    if (file == NULL) 
        return;
        char temp[100];
        int k=0;
        while(password[k]!='\0'){
            temp[k]=password[k]+3;
            k++;
        }temp[k]='\0';
    fprintf(file, "Account: %s <-----> Username: %s <-----> Password: %s\n", acc_name, username, temp);
    fclose(file);
}

void generate_stored_passwords_page() {
    FILE *vault = fopen("vault_data.txt", "r");
    FILE *html = fopen("stored_passwords.html", "w");

    if (html == NULL) return;

    fprintf(html, "<!DOCTYPE html>\n<html>\n<head>\n");
    fprintf(html, "<title>PassHub — Vault & Credential Storage</title>\n");
    fprintf(html, "</head>\n<body style='font-family: Arial, sans-serif; background-color: #f4f4f9; padding: 30px;'>\n");
    
    fprintf(html, "<div style='max-width: 95%%; margin: auto; background: #ffffff; padding: 30px; border-radius: 8px; box-shadow: 0 2px 10px rgba(0,0,0,0.1);'>\n");
    fprintf(html, "<h2 style='color: #1a283e; text-align: center;'>PassHub — Secured Password Vault</h2>\n");
    fprintf(html, "<hr style='border: 0; border-top: 1px solid #ddd;'>\n");
    
    fprintf(html, "<table border='1' cellpadding='12' cellspacing='0' style='width: 100%%; border-collapse: collapse; margin-top: 20px;'>\n");
    fprintf(html, "  <tr style='background-color: #1e293b; color: white;'><th>Account Name</th><th>Username / Email</th><th>Stored Password</th></tr>\n");

    if (vault == NULL) {
        fprintf(html, "  <tr><td colspan='3' style='text-align: center;'>No password is found yet.</td></tr>\n");
    } else {
        char line[200];
        while (fgets(line, sizeof(line), vault) != NULL) {
            char a[50], u[50], p[50];

            if (sscanf(line, "Account: %49[^<] <-----> Username: %49[^<] <-----> Password: %49s", a, u, p) == 3) {
                int l=0;
                while(p[l]!='\0'){
                    p[l]=p[l]-3;
                    l++;
                }
                fprintf(html, "  <tr><td style='word-break: break-word;'><b>%s</b></td><td style='word-break: break-word;'>%s</td><td><span style='color: #2563eb; font-weight: bold; word-break: break-word;'>%s</span></td></tr>\n", a, u, p);
            }
        }
        fclose(vault);
    }

    fprintf(html, "</table>\n");
    fprintf(html, "<br><br>\n");
    fprintf(html, "<a href='security_dashboard.html' style='text-decoration: none; background: #668dcc; color: white; padding: 10px 18px; border-radius: 5px; font-weight: bold;'>&larr; Back to Dashboard</a>\n");
    fprintf(html, "</div>\n");
    fprintf(html, "</body>\n</html>\n");
    fclose(html);
}

void generate_main_dashboard(char accs[][50], char input_passes[][100], int input_cats[], int is_accepted[], char final_passes[][100], int total) {
    FILE *html = fopen("security_dashboard.html", "w");
    if (html == NULL) return;

    fprintf(html, "<!DOCTYPE html>\n<html>\n<head>\n");
    fprintf(html, "<title>PassHub — Security Dashboard</title>\n");
    fprintf(html, "</head>\n<body style='font-family: Arial, sans-serif; background-color: #f4f4f9; padding: 30px;'>\n");
    
    fprintf(html, "<div style='max-width: 95%%; margin: auto; background: #ffffff; padding: 35px; border-radius: 8px; box-shadow: 0 2px 10px rgba(0,0,0,0.1);'>\n");
    fprintf(html, "<h2 style='color: #1e293b; text-align: center; margin-bottom: 5px;'>PassHub — Your Auditor & Vault</h2>\n");
    fprintf(html, "<p style='text-align: center; color: #547aaf;'>Password Strength & Security Audit</p>\n");
    fprintf(html, "<hr style='border: 0; border-top: 1px solid #ddd; margin-bottom: 25px;'>\n");

    for (int i = 0; i < total; i++) {
        int width = 0;
        char color[20];
        char status_text[20];

        if (input_cats[i] == 3) { width = 100; strcpy(color, "#10b981"); strcpy(status_text, "STRONG :)"); }
        else if (input_cats[i] == 2) { width = 75; strcpy(color, "#3b82f6"); strcpy(status_text, "MEDIUM!"); }
        else if (input_cats[i] == 1) { width = 50; strcpy(color, "#f59e0b"); strcpy(status_text, "AVERAGE!"); }
        else { width = 25; strcpy(color, "#ef4444"); strcpy(status_text, "POOR :("); }

        fprintf(html, "<div style='background: #f8fafc; border: 1px solid #e2e8f0; padding: 15px 20px; border-radius: 6px; margin-bottom: 20px;'>\n");
        fprintf(html, "  <p style='margin: 0 0 8px 0;'><b>Account Name:</b> <span style='color: #2563eb;'>%s</span></p>\n", accs[i]);
        fprintf(html, "  <p style='margin: 0 0 8px 0;'><b>Input Password:</b> <code>%s</code> &nbsp;||&nbsp; <b>Status:</b> <span style='color: %s; font-weight: bold;'>%s</span></p>\n", input_passes[i], color, status_text);
        
        fprintf(html, "  <div style='width: 100%%; background: #e2e8f0; border-radius: 4px; overflow: hidden; height: 16px; margin-top: 8px;'>\n");
        fprintf(html, "    <div style='width: %d%%; height: 100%%; background-color: %s;'></div>\n", width, color);
        fprintf(html, "  </div>\n");

        if (is_accepted[i] == 1) {
            fprintf(html, "  <p style='margin: 10px 0 0 0; font-size: 13px; color: #059669;'><i>Note: You accepted the suggested password. Final Password: <b>%s</b></i></p>\n", final_passes[i]);
        } else {
            fprintf(html, "  <p style='margin: 10px 0 0 0; font-size: 13px; color: #475569;'><i>Kept your own inputed password for storage.</i></p>\n");
        }
        
        fprintf(html, "</div>\n");
    }

    fprintf(html, "<br>\n");
    fprintf(html, "<div style='text-align: center;'>\n");
    fprintf(html, "<a href='stored_passwords.html' style='text-decoration: none; background: #10b981; color: white; padding: 12px 25px; border-radius: 6px; font-weight: bold; font-size: 15px;'>Click here to view Your Vault &rarr;</a>\n");
    fprintf(html, "</div>\n");
    
    fprintf(html, "</div>\n");
    fprintf(html, "</body>\n</html>\n");
    fclose(html);
}

int main() {
    char acc_name[50], username[50], password[100];
    char choice_save, choice_accept, add_more;
    
    char saved_accs[50][50];
    char input_passes[50][100];
    int input_cats[50];
    char final_passes[50][100];
    int is_accepted[50];
    int count = 0;

    srand(time(0));

    printf("\n                ***** Help Us Evaluate Your Security *****          \n\n");
    do {
        printf("\n                    ----Enter Account Details----\n");
        
        printf("\nEnter Account Name (e.g., Facebook): ");
        scanf(" %[^\n]", acc_name);
        while(getchar() != '\n'); 

        printf("\nEnter Username / Email: ");
        scanf(" %[^\n]", username);
        while(getchar() != '\n'); 

        printf("\nEnter your Password: ");
        int i = 0;
        char ch;
        while(1) {
            ch = getch();
            if (ch == 13) { 
                password[i] = '\0';
                break;
            } 
            else if (ch == 8) { 
                if (i > 0) {
                    i--;
                    printf("\b \b");
                }
            } 
            else {
                password[i] = ch;
                i++;
                printf("*");
            }
        }
        printf("\n"); 
        

        strcpy(input_passes[count], password);
        int category = analyze_password(password);
        input_cats[count] = category;

        char final_password[100];
        strcpy(final_password, password);
        int accepted = 0;

        if (category < 3) {
            char suggested_pwd[13];
            generate_strong_password(suggested_pwd);
            
            printf("\n\nAlert! Your input password security level is low/moderate!\n");
            printf("Suggested Password: %s\n", suggested_pwd);
            printf("\n\nDo you want to accept this suggested password? (y/n): ");
            scanf(" %c", &choice_accept);
            while(getchar() != '\n'); 

            if (choice_accept == 'y' || choice_accept == 'Y') {
                strcpy(final_password, suggested_pwd);
                accepted = 1;
                printf("\nSuggested password accepted!\n");
            } else {
                printf("\nYou kept your Previous password.\n");
            }
        }

        printf("\nDo you want to save this password ? (y/n): ");
        scanf(" %c", &choice_save);
        while(getchar() != '\n'); 

        if (choice_save == 'y' || choice_save == 'Y') {
            save_to_vault(acc_name, username, final_password);
            printf("\nSuccess! Password saved successfully.\n");
        } else {
            printf("\nPassword was not saved.\n");
        }

        strcpy(saved_accs[count], acc_name);
        strcpy(final_passes[count], final_password);
        is_accepted[count] = accepted;
        count++;

        printf("\nDo you want to add another account? (y/n): ");
        scanf(" %c", &add_more);
        while(getchar() != '\n'); 

    } while (add_more == 'y' || add_more == 'Y');

    generate_main_dashboard(saved_accs, input_passes, input_cats, is_accepted, final_passes, count);
    generate_stored_passwords_page();

    printf("\nAudit completed! Opening your Dashboard in browser...\n\n");
    system("start security_dashboard.html");

    return 0;
}