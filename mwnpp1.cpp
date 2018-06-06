/* com retirada das variáveis do triângulo inferior à esquerda e sem restrições de 
partição */

#include <ilcplex/ilocplex.h>
#include <iostream>
ILOSTLBEGIN

int min(int i, int k){
	if(i<k){return i;}
	return k;
}

int index(int j, int i, int n){
    i = (int) j*n+i-j*(j+1)/2;
    return i;
}

//==========================================================
// modelo com menos variáveis
//==========================================================
void MWNPP(char inst[]) {
    IloEnv env;
    try {
    	//==================================================
    	// carrega a instância
    	//==================================================

    	int n,k;
		
		ifstream entrada(inst);
		entrada  >> n;
		entrada  >> k;

		double v[n];
		
		for(int i=0;i<n;++i){
			entrada >> v[i];
		}
		
		int N = (int) (n*k - k*(k-1)/2);
		int j,i;
		//=======================================================
		// define variáveis
		//=======================================================

		IloNumVarArray x(env, N, 0, 1, ILOBOOL);
		IloNumVarArray t(env, 2, 0, IloInfinity, ILOFLOAT);

		//=========================================================
		// cria o modelo
		//=========================================================
		IloModel modelo(env);

		modelo.add(IloMinimize(env, t[1] - t[0]));
		
		for(j=0;j<k;j++){
			IloExpr Expr1(env);
			for(i=j;i<n;i++){
				Expr1 = Expr1 + v[i]*x[index(j,i,n)];
			}
			modelo.add(Expr1 - t[1] <= 0);
			modelo.add(Expr1 - t[0] >= 0);
			Expr1.end();	
		}

		for(i=0;i<n;i++){
			IloExpr Expr2(env);
			for(j=0;j<min(i+1,k);j++){
				Expr2 = Expr2 + x[index(j,i,n)];
			}
			modelo.add(Expr2 == 1);
			Expr2.end();
		}

		//================================================================
		// parametros do solver
		//================================================================
		IloCplex cplex(modelo);

		cplex.setOut(env.getNullStream());
		cplex.setWarning(env.getNullStream());
		cplex.setParam(IloCplex::Param::TimeLimit,1200);
    	cplex.setParam(IloCplex::Param::MIP::Limits::TreeMemory,3072);
    	cplex.setParam(IloCplex::Param::Threads,1);
        
        //-1, 0, 1, 2, 3
        //cplex.setParam(IloCplex::LiftProjCuts, -1);
        //cplex.setParam(IloCplex::Cliques, -1);
		//cplex.setParam(IloCplex::Covers, -1);
		//cplex.setParam(IloCplex::FlowCovers, -1);
		//cplex.setParam(IloCplex::GUBCovers, -1);
		//cplex.setParam(IloCplex::FracCuts, -1);
		//cplex.setParam(IloCplex::MIRCuts, -1);
        //cplex.setParam(IloCplex::FlowPaths, -1);
		//cplex.setParam(IloCplex::ImplBd, -1);
		//cplex.setParam(IloCplex::DisjCuts, -1);

		//cplex.setParam(IloCplex::Param::MIP::Interval, 1); // 1 para o log mais completo possível
        //cplex.setParam(IloCplex::Param::MIP::Display, 5); // informações do nó raiz
		//cplex.setOut(env.getNullStream()); // omite o log

        cplex.setParam(IloCplex::Param::MIP::Strategy::NodeSelect, 0); //0, 1, 2, 3
        cplex.setParam(IloCplex::Param::MIP::Strategy::Branch, 1); //-1, 0, 1
        cplex.setParam(IloCplex::Param::MIP::Strategy::VariableSelect, 1); //	-1, 0, 1, 2, 3, 4 
        
        cplex.solve(); 
        
		env.out()  << cplex.getStatus() << "\t" << cplex.getObjValue() << "\t"<< cplex.getBestObjValue() << "\t" << env.getTime() << endl;

        cplex.end(); //método de solução
		modelo.end(); //modelo matemático
		env.end(); // ambiente
    } catch (IloException& ex) {
        cerr << "Erro Cplex: " << ex << endl;
    } catch (...) {
        cerr << "Erro Cpp:" << endl;
    }
    
}

int main(){

	//executar ./mwnpp1 >> result1.csv

	char inst[15];
	
	for(int i=1; i<21; i++){
		
		sprintf(inst, "inst1/inst%i.txt", i);
		MWNPP(inst);

	}

	for(int i=1; i<21; i++){
		
		sprintf(inst, "inst2/inst%i.txt", i);
		MWNPP(inst);

	}

	for(int i=1; i<21; i++){
		
		sprintf(inst, "inst3/inst%i.txt", i);
		MWNPP(inst);

	}

	for(int i=1; i<21; i++){
		
		sprintf(inst, "inst4/inst%i.txt", i);
		MWNPP(inst);

	}



	return 0;
}

