#include "matrix_library.h"

// متغیرهای global
double mA[MAX][MAX], mB[MAX][MAX], mC[MAX][MAX];
double vA[MAX], vB[MAX], vC[MAX];
int rows, cols, rowsB, colsB;
int vSize, vSizeB;

// خواندن بردار
template <class T>
void ReadV (int vSize, T V[]){

    while(1){
        cout << "\nEnter the vector elements:\n";
        for(int i=0 ; i<vSize ; i++){
            cout << "Element " << i << ": ";
            cin >> V[i];
        }

        // در صورتیکه کاربر مقدار غیرصحیح وارد کند
        if (cin.fail()){
            cout << "\nERROR: Invalid input!\nTry again.\n";
            cin.clear();
            cin.ignore(1000, '\n');
        }else{
            break;
        }
    }

    // چاپ بردار
    cout << "\nThe vector you entered is:\n";
    cout << "[";
    for(int i=0 ; i<vSize ; i++){
        cout << V[i];
        if(i < vSize-1){
            cout << ", ";
        }
    }
    cout << "]\n";
}

// تابع اندازه بردار
double VMagnitude(double vec[], int size){
    double sum = 0;
    for (int i=0 ; i<size ; i++){
        sum += vec[i] * vec[i];
    }
    return sqrt(sum);
}

// تابع نرمال سازی
void VNormalize(double vec[], int size, double result[]){
    double mag = VMagnitude(vec, size);
    if(mag == 0) {
        cout << "ERROR: Cannot normalize zero vector!\n";
        cout << "Operation canceled. Returning to main menu...\n";
        return;
    }
    for(int i=0 ; i<size ; i++) {
        result[i] = (double) vec[i]/mag;
    }
}

// تابع ضرب داخلی
double VDotProduct(double vec1[], double vec2[], int size){
    double result = 0;
    for(int i=0 ; i<size ; i++) {
        result += vec1[i]*vec2[i];
    }
    return result;
}

// تابع ضرب خارجی
void VCrossProduct(double vec1[], double vec2[], double result[]){
    result[0] = vec1[1]*vec2[2] - vec1[2]*vec2[1];
    result[1] = vec1[2]*vec2[0] - vec1[0]*vec2[2];
    result[2] = vec1[0]*vec2[1] - vec1[1]*vec2[0];
    cout << result[0] << ", " << result[1] << ", " << result[2];
}

// تابع جمع دو بردار
void VAddition (double vec1[], double vec2[], int vSize){
    cout << "[";
    for(int i=0 ; i<vSize ; i++){
        cout << vec1[i] + vec2[i];
        if(i < vSize-1){
            cout << ", ";
        }
    }
    cout << "]\n";
}

// تابع تفریق دو بردار
void VSubtraction (double vec1[], double vec2[], int vSize){
    cout << "[";
    for(int i=0 ; i<vSize ; i++){
        cout << vec1[i] - vec2[i];
        if(i < vSize-1){
            cout << ", ";
        }
    }
    cout << "]\n";
}

// تابع دترمینان بازگشتی
double MDeterminantR(vector<vector<double>> M){

    int s = M.size();

    // شرظ شکستن برای ماتریس با یک درایه
    if (s == 1){
        return M[0][0];
    }

    // شرظ شکستن ماتریس 2*2
    if (s == 2){
        return M[0][0]*M[1][1] - M[0][1]*M[1][0];
    }

    double det = 0;

    for (int j=0 ; j<s ; j++){
        // ریختن ماتریس در ماتریس کوچکتر Mp
        vector<vector<double>> Mp(s-1, vector<double>(s-1));

        // پر کردن ماتریس کوچک‌تر
        for (int rows=1 ; rows<s ; rows++){ // رد کردن سطر صفرم
            int ci = 0;
            for (int cols=0 ; cols<s ; cols++){
                if (cols == j){
                    continue; // رد کردن ستونها به ترتیب
                }
                Mp[rows-1][ci] = M[rows][cols];
                ci++;
            }
        }

        // شرط بازگشت
        det += ((j%2 == 0) ? 1.0 : -1.0) * M[0][j] * MDeterminantR(Mp);
    }

    return det;
}

// تابع معکوس سازی ماتریس
void MInverse() {
    if (rows != cols) {
        cout << "\nERROR: Inverse is only for square matrix!\n";
        return;
    }

    // تبدیل به vector
    vector<vector<double>> mat(rows, vector<double>(cols));
    for (int i=0 ; i<rows ; i++){
        for (int j=0 ; j<cols ; j++){
            mat[i][j] = mA[i][j];
        }
    }

    // محاسبه دترمینان
    double det = MDeterminantR(mat);

    // چک کردن ماتریس منفرد
    if (abs(det) < 1e-10) {
        cout << "\nERROR: Matrix is singular!\n";
        cout << "Returning to menu...\n";
        return;
    }

    // ماتریس معکوس
    vector<vector<double>> inverse(rows, vector<double>(cols));

    // محاسبه همسازه‌ها
    for (int i=0 ; i<rows ; i++){
        for (int j=0 ; j<cols ; j++){
            // ریختن ماتریس در ماتریس کوچکتر mp
            vector<vector<double>> mp(rows-1, vector<double>(cols-1));

            int i2 = 0;
            for (int x=0 ; x<rows ; x++){
                if (x == i){ // حذف سطرها به ترتیب
                    continue;
                }

                int j2 = 0;
                for (int y=0 ; y<cols ; y++){
                    if (y == j){  // حذف ستونها به ترتیب
                        continue;
                    }

                    mp[i2][j2] = mat[x][y];
                    j2++;
                }
                i2++;
            }

            // محاسبه همسازه و قراردادن در ترانهاده
            double cofactor = MDeterminantR(mp);
            inverse[j][i] = (((i+j) % 2 == 0) ? 1.0 : -1.0) * cofactor / det;
        }
    }

    // نمایش معکوس
    cout << "\nThe inverse of the matrix will be:\n";
    cout << setw(15);
    for (int i=0 ; i<rows ; i++){
        for (int j=0 ; j<cols ; j++){
            cout << fixed << setprecision(3) << inverse[i][j] << setw(15);
        }
        cout << endl;
    }
    cout << "\nReturning to menu...\n";
}

// عملیات دو بردار
void twoVectorOperations(){

    while(1){
        // گرفتن سایز بردار
        cout << "\nEnter vector size (less than or equal to " << MAX << "): ";
        cin >> vSizeB;

        // در صورتیکه کاربر مقدار غیرصحیح وارد کند
        if (cin.fail()){
            cout << "\nERROR: Invalid input!\nTry again.\n";
            cin.clear();
            cin.ignore(1000, '\n');
        }else{
            break;
        }
    }

    // چک کردن درست بودن سایز بردار
    if(vSizeB<1 && vSizeB>MAX){
        cout << "\nERROR: Invalid vector size!\n";
        cout << "Returning to vector menu...\n";
        return;
    }

    // گرفتن المنتهای بردار
    ReadV(vSizeB, vB);

    int op;
    do{ // منوی دو بردار

        while(1){

            cout << "\n~~~ Two-Vector Operations ~~~\n";
            cout << "1. Addition\n";
            cout << "2. Subtraction\n";
            cout << "3. Dot product\n";
            if(vSizeB == 3){
                cout << "4. Cross product (3D only)\n";
                cout << "0. Back to vector menu\n";
            }else{
                cout << "0. Back to vector menu\n";
            }
            cout << "Choose: ";
            cin >> op;

            // در صورتیکه کاربر مقدار غیرصحیح وارد کند
            if (cin.fail()){
                cout << "\nERROR: Invalid input!\nTry again.\n";
                cin.clear();
                cin.ignore(1000, '\n');
            }else{
                break;
            }
        }

        switch(op){
            case 1: { // جمع دو بردار
                if (vSize == vSizeB){ // چک کردن شرط تفریق پذیری
                    cout << "\nThe summation will be:\n";
                    VAddition(vA, vB, vSize);
                }else{
                    cout << "\nERROR: Summation is only for vectors with the same size!\n";
                }
                cout << "Returning to menu...\n";
                break; // بازگشت به منوی دو بردار
            }

            case 2: { // تفریق دو بردار
                if (vSize == vSizeB){ // چک کردن شرط تفریق پذیری
                    cout << "\nThe difference will be:\n";
                    VSubtraction(vA, vB, vSize);
                }else{
                cout << "\nERROR: Subtraction is only for vectors with the same size!\n";
                }
                cout << "Returning to menu...\n";
                break; // بازگشت به منوی دو بردار
            }

            case 3: { // ضرب داخلی
                if (vSize == vSizeB){ // چک کردن شرط ضرب پذیری
                    double dot = VDotProduct(vA, vB, vSize);
                    cout << "\nThe result of the dot product will be: " << dot << endl;
                    cout << "Returning to menu...\n";
                }else{
                    cout << "\nERROR: Dot product is only for vectors with the same size!\n";
                }
                break; // بازگشت به منوی دو بردار
            }

            case 4: { // ضرب خارجی
                if (vSize == vSizeB){ // چک کردن شرط ضرب پذیری
                    if(vSize == 3){
                        double cross[3];
                        cout << "\nThe result of the cross product will be: ";
                        VCrossProduct(vA, vB, cross);
                        cout << "\nReturning to menu...\n";
                    }else{
                        cout << "\nCross prodoct is only for vectors with the size of 3!\n";
                        cout << "Operation canceled. Returning to menu...\n";
                        return; // بازگشت به منوی دو بردار
                    }
                }else{
                    cout << "ERROR: Cross product is only for vectors with the same size!\n";
                    cout << "Operation canceled. Returning to menu...\n";
                }
                break; // بازگشت به منوی دو بردار
            }

            case 0: { // بازگشت به منوی بردار
                cout << "\nReturning to vector menu...\n";
                break; // بازگشت به منوی بردار
            }

            default:
                cout << "\nInvalid choice! Please try again.\n";
        }
    }while(op != 0);
}

// عملیات دو ماتریس
void twoMatrixMenu(){

    int op;

    while(1){
        cout << "\nEnter the rows of the second matrix: ";
        cin >> rowsB;

        // در صورتیکه کاربر مقدار غیرصحیح وارد کند
        if (cin.fail()){
            cout << "\nERROR: Invalid input!\nTry again.\n";
            cin.clear();
            cin.ignore(1000, '\n');
        }else{
            break;
        }
    }

    while(1){
         cout << "\nEnter the columns of the second matrix: ";
         cin >> colsB;

        // در صورتیکه کاربر مقدار غیرصحیح وارد کند
        if (cin.fail()){
            cout << "\nERROR: Invalid input!\nTry again.\n";
            cin.clear();
            cin.ignore(1000, '\n');
        }else{
            break;
        }
    }

    // چک کردن درست بودن سایز ماتریس
    if (rowsB<1 && colsB<1){
        cout << "\nERROR: Dimensions must be positive! Returning to main menu...\n";
        return; // بازگشت به منوی اصلی
    }
    if (rowsB>MAX && colsB>MAX){
        cout << "\nERROR: Dimensions are too high! Returning to main menu...\n";
        return; // بازگشت به منوی اصلی
    }

    while(1){

        // خواندن ماتریس
        cout << "\nEnter the matrix elements:\n";
            for (int i=0 ; i<rowsB ; i++){
                for (int j=0 ; j<colsB ; j++){
                    cout << "mB" << "[" << i << "][" << j << "]: ";
                    cin >> mB[i][j];
                }
            }
        // در صورتیکه کاربر مقدار غیرصحیح وارد کند
        if (cin.fail()){
            cout << "\n\nERROR: Invalid input!\nTry again.\n\n";
            cin.clear();
            cin.ignore(1000, '\n');
        }else{
            break;
        }
    }


    // چاپ ماتریس
    cout << "\nThe matrix you entered will be:\n";
    cout << setw(15);
    for (int i=0 ; i<rowsB ; i++){
        for (int j=0 ; j<colsB ; j++){
            cout << mB[i][j] << setw(15);
        }
        cout << endl;
    }
    cout << endl;

    do {
        while(1){
            cout << "\n~~~ Two-Matrix Operations ~~~\n";
            cout << "1. Addition\n";
            cout << "2. Subtraction\n";
            cout << "3. Multiplication\n";
            cout << "0. Back to matrix menu\n";
            cout << "Choose: ";
            cin >> op;

            // در صورتیکه کاربر مقدار غیرصحیح وارد کند
            if (cin.fail()){
                cout << "\nERROR: Invalid input!\nTry again.\n";
                cin.clear();
                cin.ignore(1000, '\n');
            }else{
            break;
            }
        }

        switch(op){
            case 1: { // جمع دو ماتریس
                if(rows == rowsB && cols == colsB){ // چک کردن شرط جمعپذیری ماتریسها
                    cout << "\nThe addition will be:\n" << setw(15);
                    for (int i=0 ; i<rows ; i++){
                        for (int j=0 ; j<cols ; j++){
                            cout << mA[i][j] + mB[i][j] << setw(15);
                        }
                        cout << endl;
                    }
                    cout << "\nReturning to the menu...\n";

                }else{
                cout << "\nERROR: Addition is only for two matrices with the same size!\n";
                cout << "Returning to the menu...\n";
                }

                break; // بازگشت به منوی دو ماتریس
            }

            case 2: { // تفریق دو ماتریس
                if(rows == rowsB && cols == colsB){ // چک کردن شرط تفریقپذیری ماتریسها
                    cout << "\nThe subtraction will be:\n" << setw(15);
                    for (int i=0 ; i<rows ; i++){
                        for (int j=0 ; j<cols ; j++){
                            cout << mA[i][j] - mB[i][j] << setw(15);
                        }
                        cout << endl;
                    }
                    cout << "\nReturning to the menu...\n";

                }else{
                cout << "\nERROR: Subtraction is only for two matrices with the same size!\n";
                cout << "Returning to the menu...\n";
                }

                break; // بازگشت به منوی دو ماتریس
            }

            case 3: { // ضرب دو ماتریس

                if (cols != rowsB){ // چک کردن شرط ضربپذیری ماتریسها
                    cout << "\nERROR: Can not multiply matrices! Columns of mA(" << cols
                    << ") != Rows of mB(" << rowsB << ")\n";
                    cout << "Operation canceled. Returning to menu...\n";
                    break; // بازگشت به منوی دو ماتریس
                }

                // خالی کردن ماتریس سوم => برای اطمینان
                for (int i=0 ; i<MAX ; i++){
                    for (int j=0 ; j<MAX ; j++){
                        mC[i][j] = 0;
                    }
                }

                // ضرب ماتریس‌ها
                for (int i=0 ; i<rows ; i++){
                    for (int j=0 ; j<colsB ; j++){
                        for (int k=0 ; k<cols ; k++){
                            mC[i][j] += mA[i][k] * mB[k][j];
                        }
                    }
                }

                // نمایش نتیجه
                cout << "\nThe multiplication result will be:\n" << setw(15);
                for (int i=0 ; i<rows ; i++){
                    for (int j=0 ; j<colsB ; j++){
                        cout << mC[i][j] << setw(15);
                    }
                    cout << endl;
                }
                cout << "\nReturning to menu...\n";
                break; // بازگشت به منوی دو ماتریس
            }

            case 0:
                cout << "\nReturning to matrix menu...\n";
                break; // بازگشت به منوی ماتریس

            default:
                cout << "\nInvalid choice! Please try again.\n";
        }
    }while(op != 0);
}

// عنلیات بردار
void VectorOperations(){

    int choice;
    while(1){
        // گرفتن سایز بردار
        cout << "\nEnter vector size (less than or equal to " << MAX << "): ";
        cin >> vSize;

        // در صورتیکه کاربر مقدار غیرصحیح وارد کند
        if (cin.fail()){
            cout << "\nERROR: Invalid input!\nTry again.\n";
            cin.clear();
            cin.ignore(1000, '\n');
        }else{
            break;
        }
    }

    // چک کردن درست بودن سایز بردار
    if(vSize<1 && vSize>MAX){
        cout << "\nERROR: Invalid vector size!\n";
        cout << "Returning to main menu...\n";
        return;
    }

    // گرفتن المنتهای بردار
    ReadV(vSize, vA);

    // منوی اصلی بردار
    do{

        while(1){
            cout << "\n ~~~ One-Vector Operations ~~~\n";
            cout << "1. Multiply by scalar\n";
            cout << "2. Calculate magnitude\n";
            cout << "3. Normalize vector\n";
            cout << "4. Operations with 2 vectors\n";
            cout << "0. Back to main menu\n";
            cout << "Choose: ";
            cin >> choice;

            // در صورتیکه کاربر مقدار غیرصحیح وارد کند
            if (cin.fail()){
                cout << "\nERROR: Invalid input!\nTry again.\n";
                cin.clear();
                cin.ignore(1000, '\n');
            }else{
                break;
            }
        }

        switch(choice){
            case 1: { // ضرب اسکالر

            double scalar;
            while(1){
                // گرفتن سایز بردار
                cout << "\nEnter scalar: ";
                cin >> scalar;

                // در صورتیکه کاربر مقدار غیرصحیح وارد کند
                if (cin.fail()){
                    cout << "\nERROR: Invalid input!\nTry again.\n";
                    cin.clear();
                    cin.ignore(1000, '\n');
                }else{
                    break;
                }
            }

                cout << "\nThe result will be: [";
                for(int i=0 ; i<vSize ; i++){
                    cout << (double) vA[i]*scalar;
                    if(i < vSize-1){
                        cout << ", ";
                    }
                }
                cout << "]\n";
                cout << "Returning to vector menu...\n";
                break; // بازگشت به منوی بردار
            }

            case 2: { // اندازه بردار
                double mag = VMagnitude(vA, vSize);
                cout << "\nVector magnitude will be: " << mag << endl;
                cout << "Returning to vector menu...\n";
                break;
            }

            case 3: { // نرمال سازی
                double normalized[MAX];
                VNormalize(vA, vSize, normalized);

                cout << "\nThe normalized vector will be: [";
                for(int i=0 ; i<vSize ; i++){
                    cout << fixed << setprecision(3) << normalized[i];
                    if(i < vSize-1) cout << ", ";
                }
                cout << "]\n";
                cout << "Returning to vector menu...\n";
                break; // بازگشت به منوی بردار
            }

            case 4: { // اعمال با دو بردار
                twoVectorOperations();
                break; // بازگشت به منوی بردار
            }

            case 0:
                cout << "\nReturning to main menu...\n";
                break; // بازگشت به منوی اصلی

            default:
                cout << "\nInvalid choice! Please try again.\n";
        }
    }while(choice != 0);
}

// عملیات ماتریس
void MatrixOperations(){

    int choice;

    while(1){
        cout << "Enter the number of rows: ";
        cin >> rows;

        // در صورتیکه کاربر مقدار غیرصحیح وارد کند
        if (cin.fail()){
            cout << "\nERROR: Invalid input!\nTry again.\n";
            cin.clear();
            cin.ignore(1000, '\n');
        }else{
            break;
        }
    }


    while(1){
        cout << "Enter the number of columns: ";
        cin >> cols;

        // در صورتیکه کاربر مقدار غیرصحیح وارد کند
        if (cin.fail()){
            cout << "\nERROR: Invalid input!\nTry again.\n";
            cin.clear();
            cin.ignore(1000, '\n');
        }else{
            break;
        }
    }

    // چک کردن درست بودن سایز ماتریس
    if (rows<1 && cols<1){
        cout << "\nERROR: Dimensions must be positive! Returning to main menu...\n";
        return; // بازگشت به منوی اصلی
    }
    if (rows>MAX && cols>MAX){
        cout << "\nERROR: Dimensions are too high! Returning to main menu...\n";
        return; // بازگشت به منوی اصلی
    }

    while(1){
        cout << "Enter the matrix elements:\n";
        for (int i=0 ; i<rows ; i++){
            for (int j=0 ; j<cols ; j++){
                cout << "mA" << "[" << i << "][" << j << "]: ";
                cin >> mA[i][j];
            }
        }
            // در صورتیکه کاربر مقدار غیرصحیح وارد کند
        if (cin.fail()){
            cout << "\nERROR: Invalid input!\nTry again.\n";
            cin.clear();
            cin.ignore(1000, '\n');
        }else{
            break;
        }
    }

    // چاپ ماتریس
    cout << "\nThe matrix you entered is:\n";
    cout << setw(15);
    for (int i=0 ; i<rows ; i++){
        for (int j=0 ; j<cols ; j++){
            cout << mA[i][j] << setw(15);
        }
        cout << endl;
    }
    cout << endl;

    do{ // منوی اصلی ماتریس

        while(1){
            cout << "\n ~~~ One-Matrix Operations ~~~\n";
            cout << "1. Multiply by scalar\n";
            cout << "2. Transpose\n";
            cout << "3. Determinant\n";
            cout << "4. Inverse\n";
            cout << "5. Main diagonal of matrix\n";
            cout << "6. Anti-diagonal of matrix\n";
            cout << "7. Operations with 2 matrices\n";
            cout << "0. Back to main menu\n";
            cout << "Choose: ";
            cin >> choice;

            // در صورتیکه کاربر مقدار غیرصحیح وارد کند
            if (cin.fail()){
                cout << "\nERROR: Invalid input!\nTry again.\n";
                cin.clear();
                cin.ignore(1000, '\n');
            }else{
                break;
            }
        }

        switch(choice){
            case 1: { // ضرب اسکالر
                double scalar;

                while(1){
                    cout << "\nEnter scalar: ";
                    cin >> scalar;

                    // در صورتیکه کاربر مقدار غیرصحیح وارد کند
                    if (cin.fail()){
                        cout << "\nERROR: Invalid input!\nTry again.\n";
                        cin.clear();
                        cin.ignore(1000, '\n');
                    }else{
                        break;
                    }
                }

                cout << "\nThe result will be:\n" << setw(15);
                for (int i=0 ; i<rows ; i++){
                    for (int j=0 ; j<cols ; j++){
                        cout << (double) mA[i][j] * scalar << setw(15);
                    }
                    cout << endl;
                }
                cout << "Returning to matrix menu...\n";
                break; // بازگشت به منوی ماتریس
            }

            case 2: { // ترانهاده ماتریس
                cout << "\nThe transpose will be:\n" << setw(15);
                for (int j=0 ; j<cols ; j++){
                    for (int i=0 ; i<rows ; i++){
                        cout << mA[i][j] << setw(15);
                    }
                    cout << endl;
                }
                cout << "Returning to matrix menu...\n";
                break; // بازگشت به منوی ماتریس
            }

            case 3: { // دترمینان

                if (rows == cols) { // چک کردن شرط دترمینان پذیری

                    // تبدیل آرایه به بردار
                    vector<vector<double>> tempM(rows, vector<double>(cols));
                    for (int i=0 ; i<rows ; i++){
                        for (int j=0 ; j<cols ; j++){
                            tempM[i][j] = mA[i][j];
                        }
                    }

                    double det = MDeterminantR(tempM);

                    cout << "The determinant of the matrix you entered will be:\n " << det << endl;
                    cout << "Returning to matrix menu...\n";

                }else{
                    cout << "\nMatrix is not square!\n";
                    cout << "Operation canceled. Returning to matrix menu...\n";
                }
            break; // بازگشت به منوی ماتریس
            }

            case 4: { // عکس کردن

                MInverse();
                break;
            }

            case 5: { // نمایش قطر اصلی
                if (rows == cols){
                    cout << "\nThe main diagonal of the matrix will be:\n";
                    cout << "[";
                    for(int i=0 ; i<rows ; i++){
                        cout << mA[i][i];
                        if(i < rows-1){
                            cout << ", ";
                        }
                    }
                    cout << "]\n" << endl;
                    cout << "Returning to menu...\n";

                }else{
                    cout << "\nMain diagonal is only for square matrix!\n";
                    cout << "Operation canceled. Returning to matrix menu...\n";
                }
                break; // بازگشت به منوی ماتریس
            }

            case 6: { // نمایش قطر فرعی
                if (rows == cols){
                    cout << "\nThe Anti-diagonal of the matrix will be:\n";
                    cout << "[";
                    for(int i=0 ; i<rows ; i++){
                        cout << mA[i][rows-1-i];
                        if(i < rows-1){
                            cout << ", ";
                        }
                    }
                    cout << "]\n" << endl;
                    cout << "Returning to menu...\n";

                }else{
                    cout << "\nAnti-diagonal is only for square matrix!\n";
                    cout << "Operation canceled. Returning to matrix menu...\n";
                }
                break; // بازگشت به منوی ماتریس
            }

            case 7: { // اعمال با دو ماتریس
                twoMatrixMenu();
                break; // بازگشت به منوی ماتریس
            }

            case 0:
                cout << "\nReturning to main menu...\n";
                break; // بازگشت به منوی اصلی

            default: {
                cout << "\nInvalid choice!\n";
                cout << "Returning to matrix menu...\n";
            }
        }
    }while(choice != 0);
}
