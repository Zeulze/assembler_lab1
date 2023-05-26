#include <iostream>

using namespace std;

const int NUMBER_OF_INDEXES = 5;

class Asm {
public:
	int sum(int a, int b) {
		_asm {
			mov EAX, a
			add EAX, b
			mov a, EAX
		}

		return a;
	}

	int sub(int a, int b) {
		_asm {
			mov EAX, a
			sub EAX, b
			mov a, EAX
		}

		return a;
	}

	int mul(int a, int b) {
		_asm {
			mov EAX, a
			mov EBX, b
			mul EBX

			mov a, EAX
		}

		return a;
	}

	int div(int a, int b) {
		_asm {
			mov EAX, a
			mov EBX, b
			mov EDX, 0
			div EBX

			mov a, EAX
			/*mov a, EDX*/
		}

		return a;
	}
	int more(int a, int b) {
		__asm {
			mov EAX, a
			mov EBX, b
			cmp EAX, EBX
			jg bigger
			je ls
			jl ls
			

			bigger:
			mov EAX, 1
			jmp ext

			ls:
			mov EAX, 0
			jmp ext
			

			ext:
			mov a, EAX

		}
		return a;
	}

	int moreEq(int a, int b) {
		__asm {
			mov EAX, a
			mov EBX, b
			cmp EAX, EBX
			jg bigger
			je bigger
			jl ls


			bigger:
			mov EAX, 1
			jmp ext

			ls:
			mov EAX, 0
			jmp ext


			ext:
			mov a, EAX

		}
		return a;
	}

	int less(int a, int b) {
		__asm {
			mov EAX, b
			mov EBX, a
			cmp EAX, EBX
			jg bigger
			je ls
			jl ls


			bigger:
			mov EAX, 1
			jmp ext

			ls:
			mov EAX, 0
			jmp ext


			ext:
			mov a, EAX

		}
		return a;
	}

	int lessEq(int a, int b) {
		__asm {
			mov EAX, b
			mov EBX, a
			cmp EAX, EBX
			jg bigger
			je bigger
			jl ls


			bigger:
			mov EAX, 1
			jmp ext

			ls:
			mov EAX, 0
			jmp ext


			ext:
			mov a, EAX

		}
		return a;
	}

	int notOp(int a) {
		__asm {
			mov EAX, a
			mov EBX, 0
			cmp EAX, EBX
			je zero
			jg notzero

			zero:
			mov EAX, 1
			jmp ext

			notzero:
			mov EAX, 0
			jmp ext

			ext: 
			mov a, EAX

		}

		return a;
	}
	
	int orOp(int a, int b) {
		__asm {
			mov EAX, a
			mov EBX, b
			mov ECX, 0

			cmp EAX, ECX
			je nextCmp
			jl nextCmp
			jg setTrue

			nextCmp:
			cmp EBX, ECX
			je setFalse
			jl setFalse
			jg setTrue


			setTrue:
			mov EAX, 1
			jmp ext

			setFalse:
			mov EAX, 0
			jmp ext

			ext:
			mov a, EAX
		}
		
		return a;
	}

	int andOp(int a, int b) {
		__asm {
			mov EAX, a
			mov EBX, b
			mov ECX, 0

			cmp EAX, ECX
			je setFalse
			jl nextCmp
			jg nextCmp

			nextCmp:
			cmp EBX, ECX
			je setFalse
			jl setTrue
			jg setTrue


			setTrue:
			mov EAX, 1
			jmp ext

			setFalse:
			mov EAX, 0
			jmp ext

			ext:
			mov a, EAX
		}
		
		return a;
	}

	int xorOp(int a, int b) {
		__asm {
			mov EAX, a
			mov EBX, b
			mov ECX, 0

			cmp EAX, ECX
			je falseCmp
			jl trueCmp
			jg trueCmp

			falseCmp:
			cmp EBX, ECX
			jg setTrue
			jl setTrue
			je setFalse
	
			trueCmp:
			cmp EBX, ECX
			je setTrue
			jl setFalse
			jg setFalse

			setTrue:
			mov EAX, 1
			jmp ext

			setFalse:
			mov EAX, 0
			jmp ext

			ext:
			mov a, EAX
		}
		
		return a;
	}

	int indexValue(int* arr, int b) {
		
		__asm {
			mov EAX, arr
			mov EBX, b
			mov ECX, [4 * EBX + EAX]
			mov b, ECX
		}

		return b;
	}

	int shr(int a, unsigned char b) {
	
		__asm {
			mov EAX, a
			mov CL, b
			shr EAX, cl
			
			mov a, EAX
		}

		return a;
	}

	int shl(int a, unsigned char b) {

		__asm {
			mov EAX, a
			mov CL, b
			shl EAX, cl

			mov a, EAX
		}

		return a;
	}

	int sar(int a, unsigned char b) {

		__asm {
			mov EAX, a
			mov CL, b
			sar EAX, cl

			mov a, EAX
		}

		return a;
	}

	int sal(int a, unsigned char b) {

		__asm {
			mov EAX, a
			mov CL, b
			sal EAX, cl

			mov a, EAX
		}

		return a;
	}
	
};


void toSort(int* arr, int n) {
	__asm {
		mov edi, arr
		mov ecx, n


		outerloop :
		lea ebx, [edi + ecx * 4]
			mov eax, [edi]
		cmploop :
			sub ebx, 4
			cmp eax, [ebx]
			jle again
			xchg eax, [ebx]
		again :
			cmp ebx, edi
			jnz cmploop
			stosd
			loop outerloop
	};
}

int main() {
	Asm asmb;
	int arr[NUMBER_OF_INDEXES] = { 5, 4, 3, 2, 1 };
	

	cout << "Sum " << asmb.sum(10, 2) << endl
		<< "Sub " << asmb.sub(10, 2) << endl
		<< "Mul " << asmb.mul(10, 2) << endl
		<< "Div " << asmb.div(10, 2) << endl
		<< "More " << asmb.more(3, 2) << endl
		<< "More or Equal " << asmb.moreEq(3, 3) << endl
		<< "Less " << asmb.less(3, 2) << endl
		<< "Less or Equal " << asmb.lessEq(3, 3) << endl
		<< "Not " << asmb.notOp(1) << endl
		<< "Or  " << asmb.orOp(-11, 1) << endl
		<< "And  " << asmb.andOp(1, 0) << endl
		<< "Xor " << asmb.xorOp(1, 1) << endl
		<< "Value from array by index " << asmb.indexValue(arr, 3) << endl
		<< "SHR " << asmb.shr(16, 1) << endl
		<< "SHL " << asmb.shl(16, 1) << endl
		<< "SAR " << asmb.sar(-8, 1) << endl
		<< "SAL " << asmb.sal(-8, 2) << endl;
	

	cout << "\nBubble sort:\n";
	int n = 5;
	int* arrBubble = new int[n];
	srand(time(NULL));
	for (int i = 0; i < n; i++) {
		arrBubble[i] = rand() % 10;
		cout << arrBubble[i] << " ";
	}

	toSort(arrBubble, n);
	cout << endl;
	for (int i = 0; i < n; i++) {
		cout << arrBubble[i] << " ";
	}

	
}
