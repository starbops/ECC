#include <iostream>
#include <bitset>
using namespace std;

typedef long long ll;

bool Validation(ll, ll, ll, pair<ll, ll>);
pair<ll, ll> Calculate(ll, ll, pair<ll, ll>, ll);
pair<ll, ll> Addition(ll, pair<ll, ll>, pair<ll, ll>);
pair<ll, ll> Doubling(ll, ll, pair<ll, ll>);
ll FindInverse(ll, ll, ll);

int main(void) {
    ll prime = 0, a = 0, b = 0, x = 0, y = 0, multiplier = 0;
    pair<ll, ll> pointP, pointQ;

    cin >> prime >> a >> b >> x >> y >> multiplier;
    pointP = make_pair(x, y);

    if(Validation(prime, a, b, pointP)) {
        //cout << "ok" << endl;

        pointQ = Calculate(prime, a, pointP, multiplier);
        cout << pointQ.first << endl << pointQ.second << endl;
    }
    else
        cout << "wrong" << endl;

    return 0;
}

bool Validation(ll prime, ll a, ll b, pair<ll, ll> point) {
    ll x3 = 0, y2 = 0, delta = 0, lhs = 0, rhs = 0;

    delta = 4 * (a % prime) * (a % prime) * (a % prime) + 27 * (b % prime) * (b % prime);
    delta = delta % prime;

    y2 = (point.second % prime) * (point.second % prime);
    x3 = (point.first % prime) * (point.first % prime);
    x3 = (x3 % prime) * (point.first % prime);
    lhs = y2 % prime;
    rhs = (x3 % prime) + (a % prime) * (point.first % prime) + (b % prime);
    rhs = rhs % prime;

    if(delta == 0)
        return false;
    if(lhs != rhs)
        return false;
    return true;
}

pair<ll, ll> Calculate(ll prime, ll a, pair<ll, ll> P, ll multiplier) {
    bitset<32> multiplierBinary;
    int i = 0;
    pair<ll, ll> answer;

    multiplierBinary = multiplier;

    for(i = 31; i >= 0; i--)
        if(multiplierBinary[i] != 0) {
            i--;
            break;
        }
    //cout << multiplierBinary << endl;
    answer = P;
    if(i != -1) {
        for(; i >= 0; i--) {
            answer = Doubling(prime, a, answer);
            //cout << "x=" << answer.first << ", y=" << answer.second << endl;
            if(multiplierBinary[i] == 1)
                answer = Addition(prime, answer, P);
            //cout << "x=" << answer.first << ", y=" << answer.second << endl;
        }
    } else ;
    
    return answer;
}

pair<ll, ll> Addition(ll prime, pair<ll, ll> P, pair<ll, ll> Q) {
    ll lambda = 0, numerator = 0, denominator = 0;
    pair<ll, ll> answer;

    numerator = ((Q.second % prime) - (P.second % prime)) % prime;
    denominator = ((Q.first % prime) - (P.first % prime)) % prime;
    //if(numerator % denominator != 0) {
        //cout << "FUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUU" << endl;
        while(denominator < 0)
            denominator += prime;
        lambda = (numerator * FindInverse(prime, denominator, prime)) % prime;
    //} else
        //lambda = (numerator / denominator) % prime;

    answer.first = (((((lambda * lambda) % prime) - (P.first % prime)) % prime) - (Q.first % prime)) % prime;
    answer.second = ((((((P.first % prime) - (answer.first % prime)) % prime) * lambda) % prime) - (P.second % prime)) % prime;

    return answer;
}

pair<ll, ll> Doubling(ll prime, ll a, pair<ll, ll> P) {
    ll lambda = 0, numerator = 0, denominator = 0;
    pair<ll, ll> answer;

    numerator = ((((3 * (P.first % prime) % prime) * (P.first % prime)) % prime) + a) % prime;
    denominator = (2 * (P.second % prime)) % prime;
    //cout << "dsfdsf " << P.first << " " << P.second << endl;
    //cout << "dsfdsf " << numerator << " " << denominator << endl;
    //if(numerator % denominator != 0) {
        //cout << "OHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH" << endl;
        //cout << "denominator: " << denominator << endl;
        //cout << "Psecond: " << P.second << endl;
        while(denominator < 0)
            denominator += prime;
        lambda = (numerator * FindInverse(prime, denominator, prime)) % prime;
    //} else
        //lambda = (numerator / denominator) % prime;
    
    answer.first = (((lambda * lambda) % prime) - ((2 * (P.first % prime)) % prime)) % prime;
    answer.second = ((((((P.first % prime) - (answer.first % prime)) % prime) * lambda) % prime) - (P.second % prime)) % prime;

    return answer;
}

ll FindInverse(ll prime, ll a, ll b) {
    ll x[3], y[3], quotient = a / b, remainder = a % b;

    x[0] = 0;
    y[0] = 1;
    x[1] = 1;
    y[1] = (quotient * -1) % prime;

    int i = 2;
    for(; (b % (a % b)) != 0; i++) {
        a = b;
        b = remainder;
        quotient = a / b;
        remainder = a % b;
        x[i % 3] = (((((quotient * -1) % prime) * x[(i - 1) % 3]) % prime) + x[(i - 2) % 3]) % prime;
        y[i % 3] = (((((quotient * -1) % prime) * y[(i - 1) % 3]) % prime) + y[(i - 2) % 3]) % prime;
    }

    return x[(i - 1) % 3];
}
