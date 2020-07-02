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
#include <set>
#include <unistd.h>

using namespace std;

#define PBSTR "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
#define PBWIDTH 60

typedef long long int ll;
typedef unsigned long int unint;

const unint N = 140;
const unint Hamingweight = 16;
bool result = false;

struct QuarterKnapsack
{
    mpz_t sum;
    vector<int> index;
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

void stdout_vector(vector<int> v)
{
    for (int i = 0; i < v.size(); i++)
        cout << v[i] << ' ';
}
void file_vector(vector<int> &v, ofstream &outfile)
{

    for (int i = 0; i < v.size(); i++)
        outfile << v[i] << ' ';
}

void stdout_vector(vector<mpz_t *> element)
{
    for (int i = 0; i < element.size(); i++)
        gmp_printf("%Zd\n", *element[i]);
}

void stdout_vector(vector<QuarterKnapsack> v)
{
    for (int i = 0; i < v.size(); i++)
    {
        gmp_printf("%Zd ", v[i].sum);
        for (int j = 0; j < v[i].index.size(); j++)
        {
            cout << v[i].index[j] << ' ';
        }
        cout << endl;
    }
    cout << endl;
}

void insertset(set<int> &s, vector<int> &p)
{
    for (int i = 0; i < p.size(); i++)
        s.insert(p[i]);
}

void algorithm3(vector<QuarterKnapsack> &sl1, vector<QuarterKnapsack> &sr1, vector<QuarterKnapsack> &sl2,
                vector<QuarterKnapsack> &sr2,
                vector<ModuleKnapsck> &sr1m, vector<ModuleKnapsck> &sr2m,
                mpz_t target, ll M, ll Ml, ll Mr, int id)
{
    clock_t start, end;
    start = clock();
    cout << "algorm3 started" << endl;

    ll step = 0;
    // cout << Ml << ' ' << Mr << endl;
    for (unint m = Ml; m <= Mr; m++)
    {
        step++;
        if (step % 1 == 0)
        {
            double percentage = ((m - Ml) * 1.0) / (Mr - Ml);
            int val = (int)(percentage * 100);

            cout << '\n'
                 << "thread: " << id << ' '
                 << val << "% " << m << ' ' << Ml << '/' << Mr << endl;
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

        // gmp_printf("%Zd\n", s[i].sum);
        sort(s.begin(), s.end(), cmp_sol);
        // cout << s.size() << endl;
        // for (int i = 0; i < s.size(); i++)
        // {
        //     gmp_printf("%Zd ", s[i].sum);
        //     stdout_vector(sl1[s[i].sl1_index].index);
        //     cout << endl;
        // }
        // cout << "---" << endl;

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

                mpz_t tt;
                mpz_init(tt);
                mpz_sub(tt, target, sl2[sl2_index].sum);
                mpz_sub(tt, tt, sr2[sr2_index].sum);

                vector<IndexPair> return_sol = binarySearchSol(s, tt);
                mpz_clear(tt);
                // cout << return_sol.size() << endl;
                for (int sol_index = 0; sol_index < return_sol.size(); sol_index++)
                {
                    // set<int> checkset;

                    // insertset(checkset, sl1[return_sol[sol_index].i].index);
                    // insertset(checkset, sr1[return_sol[sol_index].i].index);
                    // insertset(checkset, sl2[sl2_index].index);
                    // insertset(checkset, sr2[sr2_index].index);
                    // if (checkset.size() != Hamingweight){
                    //     continue;
                    // }

                    end = clock();

                    // gmp_printf("%Zd\n", sl1[return_sol[sol_index].i].sum);
                    // gmp_printf("%Zd\n", sr1[return_sol[sol_index].i].sum);
                    // gmp_printf("%Zd\n", sl2[sl2_index].sum);
                    // gmp_printf("%Zd\n", sr2[sr2_index].index);

                    cout
                        << "\rsolved in " << (double)(end - start) / CLOCKS_PER_SEC << endl;

                    stdout_vector(sl1[return_sol[sol_index].i].index);
                    stdout_vector(sr1[return_sol[sol_index].j].index);
                    stdout_vector(sl2[sl2_index].index);
                    stdout_vector(sr2[sr2_index].index);
                    cout << endl;
                    ofstream outfile;
                    outfile.open("./outH", ios::app);
                    file_vector(sl1[return_sol[sol_index].i].index, outfile);
                    file_vector(sr1[return_sol[sol_index].j].index, outfile);
                    file_vector(sl2[sl2_index].index, outfile);
                    file_vector(sr2[sr2_index].index, outfile);
                    outfile << endl;
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

int combination(int n, int k)
{
    if (n == k || k == 0)
        return 1;
    else
        return combination(n - 1, k) + combination(n - 1, k - 1);
}

void initKnapsack(int n, int r, vector<mpz_t *> &elements,
                  vector<QuarterKnapsack> &sl1, vector<QuarterKnapsack> &sr1,
                  vector<QuarterKnapsack> &sl2, vector<QuarterKnapsack> &sr2)
{
    vector<QuarterKnapsack> tt;
    std::vector<bool> v(n);
    std::fill(v.end() - r, v.end(), true);
    int total_comb = combination(n, r);
    int comb_step = 0;
    do
    {
        double percentage = comb_step * 1.0 / total_comb;
        int val = (int)(percentage * 100);
        if (comb_step % 1000 == 0)
        {
            cout << '\r' << val << '%';
        }
        QuarterKnapsack tmp;
        mpz_init(tmp.sum);
        for (int i = 0; i < n; ++i)
        {
            if (v[i])
            {
                mpz_add(tmp.sum, tmp.sum, *elements[i]);
                tmp.index.push_back(i);
            }
        }
        tt.push_back(tmp);
        comb_step++;
    } while (std::next_permutation(v.begin(), v.end()));
    srand(time(0));
    random_shuffle(tt.begin(), tt.end());

    for (comb_step = 0; comb_step < tt.size(); comb_step++)
    {
        if (comb_step < total_comb / 4)
        {
            sl1.push_back(tt[comb_step]);
        }
        else if (comb_step < total_comb / 2)
        {
            sr1.push_back(tt[comb_step]);
        }
        else if (comb_step < 3 * total_comb / 4)
        {
            sl2.push_back(tt[comb_step]);
        }
        else
        {
            sr2.push_back(tt[comb_step]);
        }
    }
}

void howgrave(vector<mpz_t *> elements, mpz_t target, int K, int threadNumber)
{
    vector<QuarterKnapsack> sl1, sr1, sl2, sr2;
    cout << "init..." << endl;
    initKnapsack(N, K / 4, elements, sl1, sr1, sl2, sr2);
    cout << '\n';
    cout << "quarter size: " << sl1.size() << ' ' << sr1.size() << ' '
         << sl2.size() << ' ' << sr2.size() << ' ' << endl;

    double ll = pow(2, N / 4.0), rr = pow(2, (N / 4.0) + 1);
    default_random_engine e(time(0));
    uniform_real_distribution<double> u(ll, rr);
    int M = (int)u(e);
    M = pow(2, 20);
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

    // stdout_vector(sl1);
    // stdout_vector(sr1);
    // stdout_vector(sl2);
    // stdout_vector(sr2);
    // algorithm3(sl1, sr1, sl2, sr2, sr1m, sr2m, target, M, 0, M - 1, 1);
    int ml = 0, mr = M / threadNumber;

    // algorithm3(sl1, sr1, sl2, sr2, sr1m, sr2m, target, M, 0, M - 1, file);
    // thread t1(algorithm3, ref(sl1), ref(sr1), ref(sl2), ref(sr2), ref(sr1m), ref(sr2m), target, M, M /2 + 1, M-1, file);

    for (int i = 0; i < threadNumber; i++)
    {
        thread t(algorithm3, ref(sl1), ref(sr1), ref(sl2), ref(sr2), ref(sr1m), ref(sr2m), target, M, ml, mr, i + 1);
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

int main(int argc, char **argv)
{
    FILE *fp;
    char StrLine[1024];
    if ((fp = fopen("./data140", "r")) == NULL)
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

    if (argc < 2){
        cout << "[-]Error, no target" << endl;
        return 0;
    }
    char *target_str = argv[1];
    mpz_set_str(target, target_str, 10);
    gmp_printf("target %Zd\n", target);

    if (argc < 3)
    {
        cout << "[-]Error, no threadNumber" << endl;
        return 0;
    }
    int threadNumber = stoi(argv[2]);
    cout << "threadNumber: " << threadNumber << endl;
    howgrave(elements, target, Hamingweight, threadNumber);

    // mpz_clear(target);
    // for (int i = 0; i < N; i++)
    // {
    //     mpz_clear(arr[i]);
    // }
    return 0;
}
