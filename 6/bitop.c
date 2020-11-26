int getb(int c, int n) { return c>>n & 1; }
int setb(int c, int n) { return c | 1<<n; }
int clrb(int c, int n) { return c & ~(1<<n); }
int notb(int c, int n) { return c ^ 1<<n; }