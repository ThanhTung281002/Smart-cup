struct Last2 {
    int old_value = 0;
    int new_value = 0;

    void add(int value) {
        old_value = new_value;
        new_value = value;
    }
};