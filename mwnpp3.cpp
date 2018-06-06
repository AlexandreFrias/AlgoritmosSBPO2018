// modelo bruto

#include <ilcplex/ilocplex.h>
#include <iostream>
ILOSTLBEGIN

int index(int j, int i, int n){
    i = (int) j*n+i;
    return i;
}

//==========================================================
// modelo com mais variáveis
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
		
		int N = (int)(n*(k-1));
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
		
		IloExpr Expr1(env);

		for(i=0;i<n;i++){
			IloExpr Expr2(env);
			for(j=0;j<k-1;j++){
				Expr2 = Expr2 + x[index(j,i,n)];
			}
			modelo.add(Expr2 <= 1);
			Expr1 = Expr1 +v[i]*(1-Expr2);
			Expr2.end();
		}

		modelo.add(Expr1 - t[1] <= 0);
		modelo.add(Expr1 - t[0] >= 0);
		Expr1.end();
		
		for(j=0;j<k-1;j++){
			IloExpr Expr1(env);
			for(i=0;i<n;i++){
				Expr1 = Expr1 + v[i]*x[index(j,i,n)];
			}
			modelo.add(Expr1 - t[1] <= 0);
			modelo.add(Expr1 - t[0] >= 0);
			Expr1.end();	
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
        
		// env.out() << "Status = " << cplex.getStatus() << endl;
		// env.out() << "UB = " << cplex.getObjValue() << endl;
		// env.out() << "LB = " << cplex.getBestObjValue() << endl;
		// env.out() << "Tempo   = " << env.getTime() << endl;
        env.out()  << cplex.getStatus() << "\t" << cplex.getObjValue() << "\t"<< cplex.getBestObjValue() << "\t" << env.getTime() << endl;

        // FILE *fp;
        // fp = fopen("result0.txt","aw+");
        // fprintf(fp, "%f\t%f\t%f\n", cplex.getObjValue(), cplex.getBestObjValue(), env.getTime());
        // fclose(fp);

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

	//executar ./mwnpp0 >> result0.csv

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

