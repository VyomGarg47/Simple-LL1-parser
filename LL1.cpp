#include <bits/stdc++.h>
using namespace std;

class production{
private:
    int n;
    vector<char> left;
    vector<vector<string>> right;
    vector<char> ans;
    unordered_map<char,unordered_set<char>> first;
    unordered_map<char,unordered_set<char>> follow;
    unordered_set<char> visited;
    unordered_set<char> terminals;
    unordered_map<char, unordered_map<int,unordered_set<string>>> table;
    bool LLone;
    
public:
    production(const int sz){
    		LLone = true;
    	    ans.clear();
    	    first.clear();
    	    follow.clear();
    	    visited.clear();
    	    terminals.clear();
		n = sz;
    }
    void init(const vector<string> &productions){
        left.clear();
        right.clear();
        left.resize(n);
        right.resize(n);
        for(int i=0;i<(int)productions.size();++i){
		 create(productions[i],i);
	   }
    }
    
    void dfs(char v,unordered_map<char,vector<char>>&g){
        visited.insert(v);
        for(int i=0;i<(int)g[v].size();++i){
        	int curr_ch = g[v][i];
        	if(visited.count(curr_ch) == false){
        		dfs(curr_ch,g);
        	}
        }
        ans.push_back(v);
    }

    void create(string curr_production, int idx){
        string curr_right;
        bool found = false;
        for(int i=0;i<(int)curr_production.size();++i){
            if(i+1<(int)curr_production.size() and found == false and curr_production[i] == '-' and curr_production[i+1] == '>'){
                found = true;
            }
            if(found == false){
                left[idx] = curr_production[i];
            }
            else{
                curr_right.push_back(curr_production[i]);
            }
        }
        string curr;
        for(int i=0;i<(int)curr_right.size();++i){
            if(curr_right[i] == ' ' or curr_right[i] == '-' or curr_right[i] == '>'){
                continue;
            }
            if(curr_right[i] == '|'){
                right[idx].push_back(curr);
                curr.clear();
            }
            else{
                curr.push_back(curr_right[i]);
            }
        }
        right[idx].push_back(curr);
    }
    
    void calculate_first(){
    	unordered_map<char,vector<char>> g;
        for(int i=0;i<n;++i){
            for(int j=0;j<(int)right[i].size();++j){
                for(int k=0;k<(int)right[i][j].size();++k){
                    bool isnontermial = (right[i][j][k] >='A' and right[i][j][k] <= 'Z');
                    if(right[i][j][k]!='#' and !isnontermial){
                        terminals.insert(right[i][j][k]);
                    }
                }
                for(int k=0;k<(int)right[i][j].size();++k){
                    if(right[i][j][k] >='A' and right[i][j][k] <= 'Z' and left[i]!=right[i][j][k]){
                        g[left[i]].push_back(right[i][j][k]);
                    }
                    else{
                        break;
                    }
                }
            }
        }
        
        for(int i=0;i<n;++i){
        	if(visited.count(left[i]) == false){
        		dfs(left[i],g);
        	}
        };
        
        for(int i=0;i<n;++i){
            if(left[i] == ans[0]){
                for(auto &j:right[i]){
                    if(j[0] >= 'A' and j[0] <= 'Z'){
                        continue;
                    }
                    first[ans[0]].insert(j[0]);
                }
            }
        }
        for(int i=1;i<(int)ans.size();++i){
            for(int j=0;j<n;++j){
                if(left[j] == ans[i]){
                    for(auto &k:right[j]){
                        for(int l=0;l<(int)k.size();++l){
                            if(k[l] >= 'A' and k[l] <= 'Z'){
                                for(auto &x:first[k[l]]){
                                    if(x != '#'){
                                        first[ans[i]].insert(x);
                                    }
                                    else{
                                        if(l+1 == (int)k.size()){
                                            first[ans[i]].insert(x);
                                        }
                                    }
                                }
                                if(first[k[l]].find('#')==first[k[l]].end()){
                                    break;
                                }
                            }
                            else{
                                first[ans[i]].insert(k[l]);
                                break;
                            }
                        }
                    }
                }
            }
        }
        cout<<endl;
        cout<<"First : "<<endl;
        for(int i=0;i<(int)ans.size();++i){
            cout<<ans[i]<<" : ";
            for(auto &j:first[ans[i]]){
                cout<<j<<" ";
            }
            cout<<endl;
        }
    }

	void calculate_follow(){
		unordered_map<char,vector<char>> g;
		ans.clear();
		visited.clear();
		for(int i=0;i<n;++i){
			for(int j=(int)right[i].size() - 1;j>=0;--j){
				if(right[i][j].back() >= 'A' and right[i][j].back() <= 'Z' and left[i] != right[i][j].back()){
					g[right[i][j].back()].push_back(left[i]);
				}
				for(int k=(int)right[i][j].size() - 2;k>=0;--k){
					if(right[i][j][k] >='A' and right[i][j][k] <= 'Z'){
	                        char Next = right[i][j][k+1];
	                        if(Next >= 'A' and Next <= 'Z' and right[i][j][k]!=Next and first[Next].find('#')!=first[Next].end()){
	                        		g[right[i][j][k]].push_back(left[i]);
	                        }
	                        else{
	                        		break;
	                        }
	                    }
				}
			}
		}

		for(int i=0;i<n;++i){
        	if(visited.count(left[i]) == false){
        		dfs(left[i],g);
        	}
        };

		follow[left[0]].insert('$');
		int ptr = 0;
		while(ptr < 2){
			for(int x=0;x<n;++x){
				for(int i=0;i<n;++i){
					for(int j=(int)right[i].size() - 1;j>=0;--j){
						unordered_set<char> curr_follow_set;
						for(auto &z:follow[left[i]]){
							if(z != '#'){
								curr_follow_set.insert(z);
							}
						}
						for(int k=(int)right[i][j].size() - 1;k>=0;--k){
							if(right[i][j][k] == ans[x]){
								for(auto &z:curr_follow_set){
									follow[ans[x]].insert(z);
								}
			                    }
			                    else{
			                    	if(right[i][j][k] >= 'A' and right[i][j][k] <= 'Z'){
			                    		if(first[right[i][j][k]].find('#') != first[right[i][j][k]].end()){
			                    			for(auto &z:first[right[i][j][k]]){
			                    				if(z != '#'){
			                    					curr_follow_set.insert(z);
			                    				}
			                    			}
			                    		}
			                    		else{
			                    			curr_follow_set.clear();
			                    			for(auto &z:first[right[i][j][k]]){
			                    				curr_follow_set.insert(z);
			                    			}
			                    		}
			                    	}
			                    	else{
			                    		curr_follow_set.clear();
			                    		if(right[i][j][k]!='#'){
			                    			curr_follow_set.insert(right[i][j][k]);
			                    		}
			                    	}
			                    }
						}
					}
				}
			}
			ptr++;
		}
        cout<<endl;
        cout<<"Follow : "<<endl;
        for(int i=0;i<(int)ans.size();++i){
            cout<<ans[i]<<" : ";
            for(auto &j:follow[ans[i]]){
                cout<<j<<" ";
            }
            cout<<endl;
        }
	}
    void generate_table(bool display = true){
        terminals.insert('$');
        for(int i=0;i<n;++i){
            for(int j=0;j<(int)right[i].size();++j){
                unordered_set<char> curr_first;
                for(int k=0;k<(int)right[i][j].size();++k){
                    char curr_symbol = right[i][j][k];
                    bool isnontermial = (right[i][j][k] >='A' and right[i][j][k] <= 'Z');
                    if(!isnontermial){
                        if(curr_symbol == '#'){
                            curr_first.insert('#');
                            break;
                        }
                        else{
                            curr_first.insert(curr_symbol);
                            break;
                        }
                    }
                    else{
                        for(auto &x:first[curr_symbol]){
                            curr_first.insert(x);
                        }
                        if(first[curr_symbol].find('#')==first[curr_symbol].end()){
                            break;
                        }
                    }
                }
                for(auto &x:curr_first){
                    string extra = {left[i]};
                    extra = extra + "->" + right[i][j];
                    if(x != '#') table[left[i]][x].insert(extra);
                }
                if(curr_first.find('#')!=curr_first.end()){
                    for(auto &x:follow[left[i]]){
                        string extra = {left[i]};
                        extra = extra + "->" + right[i][j];
                        table[left[i]][x].insert(extra);
                    }
                }
            }
        }
        if(display){
        	  cout<<endl<<"LL(1) table"<<endl;
        	  unordered_map<char,int> col_width;
        	  for(int i=0;i<n;++i){
        	  	for(auto &x:terminals){
        	  		int curr = 0;
        	  		if(table[left[i]][x].size() == 0){
        	  			curr = 6;
        	  		}
        	  		else{
	        	  		for(auto &y:table[left[i]][x]){
	        	  			curr += y.size()+1;
	        	  		}
        	  		}
        	  		col_width[x] = max(col_width[x], curr);
        	  	}
        	  }
        	  int row_len = 3;
        	  cout<<"   ";
        	  for(auto &x:terminals){
        	  	cout<<setw(col_width[x]-1)<<x<<"  |";
        	  	row_len += col_width[x]-1 + 3;
        	  }
        	  cout<<endl;
        	  for(int i=0;i<row_len;++i){
        	  	cout<<"-";
        	  }
        	  cout<<endl;
            for(int i=0;i<n;++i){
            	 cout<<left[i]<<" |";
                for(auto &x:terminals){
                	cout<<setw(col_width[x]);
                	if(table[left[i]][x].size() == 0){
                		cout<<"error ";
                	}
                	else{
                		string z;
	                    for(auto &y: table[left[i]][x]){
	                    	z += y + " ";
	                    }
	                    if(table[left[i]][x].size() > 1){
	                    	LLone = false;
	                    }
	                    cout<<z;
               	}
               	cout<<" |";
                }
                cout<<endl;
            }
            cout<<endl;
        }
    }    
    void parse_string(string input){
        if(!LLone){
            cout<<"Grammar is not LL1"<<endl;
            return;
        }
        input.push_back('$');
        stack<char>s;
        s.push('$');
        s.push(left[0]);
        int ptr = 0;
        bool f = true;
        while(ptr<(int)input.length() and s.empty() == false){
            char curr = s.top();
            s.pop();
            bool isnontermial = (curr >= 'A' and curr <= 'Z');
            if(isnontermial){
                if(table[curr][input[ptr]].size() == 0 or table[curr][input[ptr]].size() > 1){
                    f = false;
                    break;
                }
                else{
                    string cc = (*table[curr][input[ptr]].begin());
                    if(cc.back() =='#'){
                        continue;
                    }
                    for(int i=(int)cc.length() - 1; i>=0;--i){
                    	if(cc[i] == '>' or cc[i] == '-'){
                    		break;
                    	}
                        s.push(cc[i]);
                    }
                }
            }
            else{
                if(input[ptr] == curr){
                    ptr++;
                    continue;
                }
                else{
                    f = false;
                    break;
                }
            }
        }
        while(s.empty() == false){
        	cout<<s.top()<<endl;
        	s.pop();
        }
        if(s.empty() and f){
            cout<<"Parsed successfully"<<endl;
        }
        else{
            cout<<"Not Parsed!"<<endl;
        }
    }
};

int main(int argc, char const *argv[]) {
	int n;
	cin>>n;
	vector<string> productions(n);
	for(int i=0;i<n;++i){
	    cin>>productions[i];
	}
	string input;
	cin>>input;
	production p(n);
	p.init(productions);
	p.calculate_first();
	p.calculate_follow();
	p.generate_table();
	//p.parse_string(input);
	return 0;
}

/*
5
E->TA
A->+TA|#
T->FB
B->*FB|#
F->(E)|i
i+i*i
*/