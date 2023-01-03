
#include <bits/stdc++.h>
using namespace std;

class Relation {
public:
bool checkPartialOrder(set<int> A,set<pair<int, int> > R)
    {
        bool transitive = checkTransitive(R);
        bool antisymmetric = checkAntiSymmetric(R);
        bool reflexive = checkReflexive(A, R);
        return (transitive && antisymmetric && reflexive);
    }
	bool checkEquivalence(set<int> A, set<pair<int, int> > R) {
		bool transitive = checkTransitive(R);
		bool symmetric = checkSymmetric(R);
		bool reflexive = checkReflexive(A, R);
		return (transitive && symmetric && reflexive);
	}

	bool checkTransitive(set<pair<int, int> > R) {
		if (R.size() == 0) {
			return true;
		}

		map<int, set<int> > tup;

		for (auto i = R.begin(); i != R.end(); i++) {
			if (tup.find(i->first) == tup.end()) {
				set<int> temp;
				temp.insert(i->second);
				tup.insert(
					pair<int, set<int> >(i->first, temp));
			}
			else {
				tup.at(i->first).insert(i->second);
			}
		}

		for (auto a = tup.begin(); a != tup.end(); a++) {

			set<int> all_b_in_aRb = tup.at(a->first);

			for (int b : all_b_in_aRb) {
				if (tup.find(b) != tup.end()
					&& a->first != b) {

					set<int> all_c_in_bRc = tup.at(b);

				
					for (int c : all_c_in_bRc) {
						if (all_b_in_aRb.find(c)
							== all_b_in_aRb.end()) {
							return false;
						}
					}
				}
			}
		}

		return true;
	}
	bool checkAntiSymmetric(set<pair<int, int> > R)
    {
        if (R.size() == 0) {
            return true;
        }
 
        for (auto i = R.begin(); i != R.end(); i++) {
            if (i->second != i->first) {
 
               
                auto temp = make_pair(i->second, i->first);
 
                if (R.find(temp) != R.end()) {
                  
                    return false;
                }
            }
        }
 
        return true;
    }

	bool checkSymmetric(set<pair<int, int> > R) {
		if (R.size() == 0) {
			return true;
		}

		for (auto i = R.begin(); i != R.end(); i++) {

			auto temp = make_pair(i->second, i->first);

			if (R.find(temp) == R.end()) {

			
				return false;
			}
		}

		return true;
	}

	bool checkReflexive(set<int> A, set<pair<int, int> > R) {
		if (A.size() > 0 && R.size() == 0) {
			return false;
		}
		else if (A.size() == 0) {
			return true;
		}

		for (auto i = A.begin(); i != A.end(); i++) {

			auto temp = make_pair(*i, *i);

			if (R.find(temp) == R.end()) {

			
				return false;
			}
		}

		return true;
	}
};

int main()
{
	// Creating a set A
	set<int> A{ 1, 2, 3, 4 };

	set<pair<int, int> > R;


	R.insert(make_pair(1, 1));
	R.insert(make_pair(1, 3));
	R.insert(make_pair(2, 2));
	R.insert(make_pair(3, 3));
	R.insert(make_pair(3, 1));
	R.insert(make_pair(3, 4));
	R.insert(make_pair(4, 4));
	R.insert(make_pair(4, 3));

	Relation obj;

	
	if (obj.checkEquivalence(A, R)) {
		cout << "Equivalence Relation" << endl;
	}
	else if(obj.checkPartialOrder(A,R)) {
		cout << "Partial order relation " << endl;
	}else{
	    cout<<"Not a equivalence nor partial order"<<endl;
	}

	return 0;
}
