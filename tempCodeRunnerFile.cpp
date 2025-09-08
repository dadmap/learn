 for (int i = 0; i < *n; i++) {
        if (fscanf(file, "%lf", &x[i]) < 1) {
            printf("Ошибка чтения из файла '%s'\n", fname);
            fclose(file);
            return 0;