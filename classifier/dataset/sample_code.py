# dataset/sample_code.py
class SampleCodeGenerator:
    @staticmethod
    def generate_c_codes():
        return [
            """
            #include <stdio.h>
            int main() {
                int a = 10, b = 20;
                printf("%d\\n", a + b);
                return 0;
            }
            """,
            """
            #include <stdio.h>
            int fib(int n) {
                if (n <= 1) return n;
                return fib(n-1) + fib(n-2);
            }
            int main() {
                printf("%d\\n", fib(10));
                return 0;
            }
            """,
            """
            #include <stdlib.h>
            int main() {
                int *p = malloc(10 * sizeof(int));
                for(int i=0;i<10;i++) p[i]=i;
                free(p);
                return 0;
            }
            """,
            """
            int square(int x){ return x*x; }
            int main(){
                return square(5);
            }
            """,
            """
            #include <stdio.h>
            int main(){
                for(int i=0;i<5;i++)
                    printf("%d ", i);
                return 0;
            }
            """
        ]

    @staticmethod
    def generate_cpp_codes():
        return [
            """
            #include <iostream>
            int main(){
                std::cout << "Hello" << std::endl;
                return 0;
            }
            """,
            """
            #include <vector>
            #include <iostream>
            int main(){
                std::vector<int> v = {1,2,3};
                for(auto x:v) std::cout<<x;
                return 0;
            }
            """,
            """
            #include <iostream>
            class A {
            public:
                virtual void f(){ std::cout<<"A"; }
            };
            int main(){
                A a;
                a.f();
                return 0;
            }
            """,
            """
            #include <iostream>
            template<typename T>
            T add(T a, T b){ return a+b; }
            int main(){
                std::cout << add(2,3);
                return 0;
            }
            """,
            """
            #include <string>
            int main(){
                std::string s = "test";
                return s.size();
            }
            """
        ]
