#include <iostream>
#include <gmp.h>
#include <vector>
#include <random>
#include <string>
#include <ctime>
#include <algorithm>
#include <time.h>
#include <thread>
#include <stdlib.h>
#include <fstream>
#include <unistd.h>

using namespace std;

#define PBSTR "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
#define PBWIDTH 60

typedef long long int ll;
typedef unsigned long int unint;

const unint N = 100;
const unint Hamingweight = 12;
const int threadNumber = 7;
const char *target_str = "9087220043175866097535766528017";
bool result = false;

struct QuarterKnapsack
{
    mpz_t sum;
    unint weight;
};

struct ModuleKnapsck
{
    unint sum;
    unint index;
};



struct IndexPair
{
    unint i;
    unint j;
};

class Solution
{
public:
    mpz_t sum;
    unint sl1_index;
    unint sr1_index;
    Solution() { mpz_init(this->sum); };
    ~Solution();
};

Solution::~Solution()
{
    // mpz_clear(this->sum);
    // mpz_realloc2(this->sum, 0);
}


vector<QuarterKnapsack> init(int l, int r, vector<mpz_t *> elements)
{

    unint last, lent = r - l + 1;
    vector<QuarterKnapsack> slist;
    for (ll i = 0; i < pow(2, lent); i++)
    {
        unint count = 0, value = i, HMW = 0;
        mpz_t sum;
        mpz_init(sum);
        while (value > 0)
        {
            last = value & 0x01;
            if (last == 1)
            {
                mpz_add(sum, sum, *elements[r - count]);
                HMW++;
            }
            count++;
            value = value >> 1;
        }
        if (HMW > Hamingweight)
        {
            continue;
        }
        QuarterKnapsack oneKapk;
        mpz_init(oneKapk.sum);
        mpz_set(oneKapk.sum, sum);
        oneKapk.weight = HMW;
        slist.push_back(oneKapk);

        mpz_clear(sum);
    }
    return slist;
}

vector<unint> binarySearch(vector<ModuleKnapsck> &slist, unint x)
{
    ll l = 0, r = slist.size() - 1, mid;
    vector<unint> ans;
    while (l <= r)
    {
        mid = (l + r) / 2;

        if (slist[mid].sum == x)
        {
            for (ll i = mid - 1; i > -1; i--)
            {
                if (slist[i].sum == x)
                {
                    ans.push_back(slist[i].index);
                }
                else
                {
                    break;
                }
            }
            ans.push_back(slist[mid].index);
            for (ll i = mid + 1; i < slist.size(); i++)
            {
                if (slist[i].sum == x)
                {
                    ans.push_back(slist[i].index);
                }
                else
                {
                    break;
                }
            }
            return ans;
        }
        else if (slist[mid].sum > x)
        {
            r = mid - 1;
        }
        else
        {
            l = mid + 1;
        }
    }
    return ans;
}

vector<IndexPair> binarySearchSol(vector<Solution> &slist, mpz_t x)
{
    int l = 0, r = slist.size() - 1, mid;
    vector<IndexPair> ans;
    IndexPair solpair;
    while (l <= r)
    {
        mid = (l + r) / 2;
        if (mpz_cmp(slist[mid].sum, x) == 0)
        {
            for (ll i = mid - 1; i > -1; i--)
            {
                if (slist[i].sum == x)
                {
                    solpair.i = slist[i].sl1_index;
                    solpair.j = slist[i].sr1_index;
                    ans.push_back(solpair);
                }
                else
                {
                    break;
                }
            }
            solpair.i = slist[mid].sl1_index;
            solpair.j = slist[mid].sr1_index;
            ans.push_back(solpair);
            for (ll i = mid + 1; i < slist.size(); i++)
            {
                if (slist[i].sum == x)
                {
                    solpair.i = slist[i].sl1_index;
                    solpair.j = slist[i].sr1_index;
                    ans.push_back(solpair);
                }
                else
                {
                    break;
                }
            }
            return ans;
        }
        else if (mpz_cmp(slist[mid].sum, x) == 1)
        {
            r = mid - 1;
        }
        else
        {
            l = mid + 1;
        }
    }
}

bool cmp_mod(ModuleKnapsck x, ModuleKnapsck y)
{
    return x.sum < y.sum;
}

bool cmp_sol(Solution x, Solution y)
{
    return (mpz_cmp(x.sum, y.sum) < 0);
}

void algorithm3(vector<QuarterKnapsack> &sl1, vector<QuarterKnapsack> &sr1, vector<QuarterKnapsack> &sl2,
                vector<QuarterKnapsack> &sr2, \
                vector<ModuleKnapsck> &sr1m, vector<ModuleKnapsck> &sr2m,
                mpz_t target,ll M, ll Ml, ll Mr, \
                int id, ofstream &record)
{
    
    clock_t start, end;
    start = clock();
    cout << "algorm3 started" << endl;



    ll step = 0;
    // cout << Ml << ' ' << Mr << endl;
    for (unint m = Ml; m <= Mr; m++)
    {
        step++;
        if (step % 10 == 0)
        {
            double percentage = ((m - Ml) * 1.0) / (Mr - Ml);
            int val = (int)(percentage * 100);
            
            cout << '\n'
                     << "thread: " << id << ' ' << val << "% " << m << ' ' << Ml << '/' << Mr << endl;
            if (step % 500 == 0){
                record << '\n'
                       << "thread: " << id << ' ' << val << "% " << m << ' ' << Ml << '/' << Mr << endl;
            }
            
        }

        vector<Solution> s;
        for (unint sl1_index = 0; sl1_index < sl1.size(); sl1_index++)
        {
            mpz_t tmp;
            mpz_init(tmp);
            mpz_ui_sub(tmp, m, sl1[sl1_index].sum);
            vector<unint> return_list = binarySearch(sr1m, mpz_fdiv_ui(tmp, M));
            mpz_clear(tmp);

            for (int i = 0; i < return_list.size(); i++)
            {
                unint sr1_index = return_list[i];
                unint HMW = sl1[sl1_index].weight + sr1[sr1_index].weight;
                if (HMW <= Hamingweight)
                {
                    mpz_t sum;
                    mpz_init(sum);
                    mpz_add(sum, sl1[sl1_index].sum, sr1[sr1_index].sum);
                    Solution sol;
                    mpz_set(sol.sum, sum);
                    sol.sl1_index = sl1_index;
                    sol.sr1_index = sr1_index;
                    s.push_back(sol);
                    mpz_clear(sum);
                }
            }
        }
        
        // gmp_printf("%Zd\n", s[i].sum);
        sort(s.begin(), s.end(), cmp_sol);

        for (int sl2_index = 0; sl2_index < sl2.size(); sl2_index++)
        {
            mpz_t tmp;
            mpz_init(tmp);
            mpz_sub_ui(tmp, target, m);
            mpz_sub(tmp, tmp, sl2[sl2_index].sum);

            vector<unint> return_list = binarySearch(sr2m, mpz_fdiv_ui(tmp, M));
            mpz_clear(tmp);
            for (int i = 0; i < return_list.size(); i++)
            {
                unint sr2_index = return_list[i];

                unint HMW = sl2[sl2_index].weight + sr2[sr2_index].weight;
                if (HMW > Hamingweight)
                {
                    continue;
                }
                mpz_t tt;
                mpz_init(tt);
                mpz_sub(tt, target, sl2[sl2_index].sum);
                mpz_sub(tt, tt, sr2[sr2_index].sum);

                vector<IndexPair> return_sol = binarySearchSol(s, tt);
                mpz_clear(tt);
                
                for (int sol_index = 0; sol_index < return_sol.size(); sol_index++)
                {
                    FILE *file;
                    file = fopen("./outT", "w");

                    end = clock();
                    cout << "\rsolved in " << (double)(end - start) / CLOCKS_PER_SEC << endl;
                    mpz_out_str(file, 10, sl1[return_sol[sol_index].i].sum), fputc('\n', file);
                    mpz_out_str(file, 10, sr1[return_sol[sol_index].j].sum), fputc('\n', file);
                    mpz_out_str(file, 10, sl2[sl2_index].sum), fputc('\n', file);
                    mpz_out_str(file, 10, sr2[sr2_index].sum);
                    fclose(file);
                    result = true;
                    return;
                }
                
            }
        }
        for (int i = 0; i < s.size(); i++)
            mpz_clear(s[i].sum);
        s.clear();
    }
}


void shamir(vector<mpz_t *> elements, mpz_t target)
{
    int quarter = elements.size() / 4;
    cout << "qater :" << quarter << endl;
    vector<QuarterKnapsack> sl1 = init(0, quarter - 1, elements);
    cout << "int 1 " << sl1.size() << endl;
    vector<QuarterKnapsack> sr1 = init(quarter, 2 * quarter - 1, elements);
    cout << "int 2 " << sr1.size() << endl;
    vector<QuarterKnapsack> sl2 = init(2 * quarter, 3 * quarter - 1, elements);
    cout << "int 3 " << sl2.size() << endl;
    vector<QuarterKnapsack> sr2 = init(3 * quarter, elements.size() - 1, elements);
    cout << "int 4 " << sr2.size() << endl;

    double ll = pow(2, N / 4.0), rr = pow(2, (N / 4.0) + 1);
    default_random_engine e(time(0));
    uniform_real_distribution<double> u(ll, rr);
    int M = (int)u(e);
    cout << "Mod: " << M << endl;

    cout << "init module" << endl;
    vector<ModuleKnapsck> sr1m;
    for (int i = 0; i < sr1.size(); i++)
    {
        ModuleKnapsck _t;
        _t.sum = mpz_fdiv_ui(sr1[i].sum, M), _t.index = i;
        sr1m.push_back(_t);
    }

    vector<ModuleKnapsck> sr2m;
    for (int i = 0; i < sr2.size(); i++)
    {
        ModuleKnapsck _t;
        _t.sum = mpz_fdiv_ui(sr2[i].sum, M), _t.index = i;
        sr2m.push_back(_t);
    }

    cout << "sorting" << endl;
    sort(sr1m.begin(), sr1m.end(), cmp_mod);
    sort(sr2m.begin(), sr2m.end(), cmp_mod);
    cout << "sort completed" << endl;

    int ml = 0, mr = M / threadNumber;

    // algorithm3(sl1, sr1, sl2, sr2, sr1m, sr2m, target, M, 0, M - 1, file);
    // thread t1(algorithm3, ref(sl1), ref(sr1), ref(sl2), ref(sr2), ref(sr1m), ref(sr2m), target, M, M /2 + 1, M-1, file);

    ofstream record;
    record.open("./record");

    for (int i = 0; i < threadNumber; i++)
    {
        thread t(algorithm3, ref(sl1), ref(sr1), ref(sl2), ref(sr2), ref(sr1m), ref(sr2m), target, M, ml, mr, i + 1, ref(record));
        t.detach();
        ml = mr + 1;
        mr += M / threadNumber + 1;
        if (abs(M - mr) < threadNumber)
        {
            mr = M - 1;
        }
    }
    while (result == false)
    {
        sleep(5);
        /* code */
    }
    
}

int main()
{
    FILE *fp;
    char StrLine[1024];
    if ((fp = fopen("./data100", "r")) == NULL)
    {
        cout << ("[-]Error, can't open file") << endl;
        return -1;
    }

    vector<mpz_t *> elements;
    mpz_t arr[N];

    for (int i = 0; i < N; i++)
    {
        mpz_init(arr[i]);
        mpz_set_str(arr[i], fgets(StrLine, 1024, fp), 10);
        elements.push_back(arr + i);
    }
    fclose(fp);
    mpz_t target;
    mpz_init(target);
    mpz_set_str(target, target_str, 10);

    shamir(elements, target);

    mpz_clear(target);
    for (int i = 0; i < N; i++){
        mpz_clear(arr[i]);
    }
    return 0;
}
