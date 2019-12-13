#include <iostream>
#include <string>

#include "Pass2Visitor.h"
#include "wci/intermediate/SymTabStack.h"
#include "wci/intermediate/SymTabEntry.h"
#include "wci/intermediate/TypeSpec.h"
#include "wci/intermediate/symtabimpl/Predefined.h"

using namespace wci;
using namespace wci::intermediate;
using namespace wci::intermediate::symtabimpl;

unsigned long int loopLabels = 0;
unsigned long int ifLabels = 0;
unsigned long globalBranch = 0;
bool ifORLoop = false; //false for if true for loop

Pass2Visitor::Pass2Visitor(ostream& j_file)
    : program_name(""), j_file(j_file)
{
}

Pass2Visitor::~Pass2Visitor() {}

antlrcpp::Any Pass2Visitor::visitProgram(Pcl2Parser::ProgramContext *ctx)
{
    auto value = visitChildren(ctx);
    //j_file.close();
    return value;
}

antlrcpp::Any Pass2Visitor::visitHeader(Pcl2Parser::HeaderContext *ctx)
{
    program_name = ctx->IDENTIFIER()->toString();
    return visitChildren(ctx);
}

antlrcpp::Any Pass2Visitor::visitMainBlock(Pcl2Parser::MainBlockContext *ctx)
{
    // Emit the main program header.
    j_file << endl;
    j_file << ".method public static main([Ljava/lang/String;)V" << endl;
    j_file << endl;
    j_file << "\tnew RunTimer" << endl;
    j_file << "\tdup" << endl;
    j_file << "\tinvokenonvirtual RunTimer/<init>()V" << endl;
    j_file << "\tputstatic        " << program_name
           << "/_runTimer LRunTimer;" << endl;
    j_file << "\tnew PascalTextIn" << endl;
    j_file << "\tdup" << endl;
    j_file << "\tinvokenonvirtual PascalTextIn/<init>()V" << endl;
    j_file << "\tputstatic        " + program_name
           << "/_standardIn LPascalTextIn;" << endl;

    auto value = visitChildren(ctx);

    // Emit the main program epilogue.
    j_file << endl;
    j_file << "\tgetstatic     " << program_name
               << "/_runTimer LRunTimer;" << endl;
    j_file << "\tinvokevirtual RunTimer.printElapsedTime()V" << endl;
    j_file << endl;
    j_file << "\treturn" << endl;
    j_file << endl;
    j_file << ".limit locals 16" << endl;
    j_file << ".limit stack 16" << endl;
    j_file << ".end method" << endl;

    return value;
}

antlrcpp::Any Pass2Visitor::visitStmt(Pcl2Parser::StmtContext *ctx)
{
    j_file << endl << "; " + ctx->getText() << endl << endl;

    return visitChildren(ctx);
}

antlrcpp::Any Pass2Visitor::visitAssignmentStmt(Pcl2Parser::AssignmentStmtContext *ctx)
{
    auto value = visit(ctx->expr());

    string type_indicator =
                  (ctx->expr()->type == Predefined::integer_type) ? "I"
                : (ctx->expr()->type == Predefined::real_type)    ? "F"
                :                                                   "?";

    // Emit a field put instruction.
    j_file << "\tputstatic\t" << program_name
           << "/" << ctx->variable()->IDENTIFIER()->toString()
           << " " << type_indicator << endl;

    return value;
}

antlrcpp::Any Pass2Visitor::visitAddSubExpr(Pcl2Parser::AddSubExprContext *ctx)
{
    auto value = visitChildren(ctx);

    TypeSpec *type1 = ctx->expr(0)->type;
    TypeSpec *type2 = ctx->expr(1)->type;

    bool integer_mode =    (type1 == Predefined::integer_type)
                        && (type2 == Predefined::integer_type);
    bool real_mode    =    (type1 == Predefined::real_type)
                        && (type2 == Predefined::real_type);

    string op = ctx->addSubOp()->getText();
    string opcode;

    if (op == "+")
    {
        opcode = integer_mode ? "iadd"
               : real_mode    ? "fadd"
               :                "????";
    }
    else
    {
        opcode = integer_mode ? "isub"
               : real_mode    ? "fsub"
               :                "????";
    }

    // Emit an add or subtract instruction.
    j_file << "\t" << opcode << endl;

    return value;
}

antlrcpp::Any Pass2Visitor::visitMulDivExpr(Pcl2Parser::MulDivExprContext *ctx)
{
    auto value = visitChildren(ctx);

    TypeSpec *type1 = ctx->expr(0)->type;
    TypeSpec *type2 = ctx->expr(1)->type;

    bool integer_mode =    (type1 == Predefined::integer_type)
                        && (type2 == Predefined::integer_type);
    bool real_mode    =    (type1 == Predefined::real_type)
                        && (type2 == Predefined::real_type);

    string op = ctx->mulDivOp()->getText();
    string opcode;

    if (op == "*")
    {
        opcode = integer_mode ? "imul"
               : real_mode    ? "fmul"
               :                "????";
    }
    else
    {
        opcode = integer_mode ? "idiv"
               : real_mode    ? "fdiv"
               :                "????";
    }

    // Emit a multiply or divide instruction.
    j_file << "\t" << opcode << endl;

    return value;
}

antlrcpp::Any Pass2Visitor::visitVariableExpr(Pcl2Parser::VariableExprContext *ctx)
{
    string variable_name = ctx->variable()->IDENTIFIER()->toString();
    TypeSpec *type = ctx->type;

    string type_indicator = (type == Predefined::integer_type) ? "I"
                          : (type == Predefined::real_type)    ? "F"
                          :                                      "?";

    // Emit a field get instruction.
    j_file << "\tgetstatic\t" << program_name
           << "/" << variable_name << " " << type_indicator << endl;

    return visitChildren(ctx);
}

antlrcpp::Any Pass2Visitor::visitSignedNumber(Pcl2Parser::SignedNumberContext *ctx)
{
    auto value = visitChildren(ctx);
    TypeSpec *type = ctx->number()->type;

    if (ctx->sign()->children[0] == ctx->sign()->SUB_OP())
    {
        string opcode = (type == Predefined::integer_type) ? "ineg"
                      : (type == Predefined::real_type)    ? "fneg"
                      :                                      "?neg";

        // Emit a negate instruction.
        j_file << "\t" << opcode << endl;
    }

    return value;
}

antlrcpp::Any Pass2Visitor::visitIntegerConst(Pcl2Parser::IntegerConstContext *ctx)
{
    // Emit a load constant instruction.
    j_file << "\tldc\t" << ctx->getText() << endl;

    return visitChildren(ctx);
}

antlrcpp::Any Pass2Visitor::visitFloatConst(Pcl2Parser::FloatConstContext *ctx)
{
    // Emit a load constant instruction.
    j_file << "\tldc\t" << ctx->getText() << endl;

    return visitChildren(ctx);
}

antlrcpp::Any Pass2Visitor::visitPrintStmt(Pcl2Parser::PrintStmtContext *ctx)
{
    // Get the format string without the surrounding the single quotes.
    string str = ctx->formatString()->getText();
    string format_string = str.substr(1, str.length() - 2);

    // Emit code to push the java.lang.System.out object.
    j_file << "\tgetstatic\tjava/lang/System/out Ljava/io/PrintStream;" << endl;

    // Emit code to push the format string.
    j_file << "\tldc\t\"" << format_string << "\"" << endl;

    // Array size is the number of expressions to evaluate and print.
    int array_size = ctx->printArg().size();

    // Emit code to create the array of the correct size.
    j_file << "\tldc\t" << array_size << endl;
    j_file << "\tanewarray\tjava/lang/Object" << endl;

    // Loop to generate code for each expression.
    for (int i = 0; i < array_size; i++)
    {
        j_file << "\tdup" << endl;        // duplicate the array address
        j_file << "\tldc\t" << i << endl;  // array element index

        // Emit code to evaluate the expression.
        visit(ctx->printArg(i)->expr());
        TypeSpec *type = ctx->printArg(i)->expr()->type;

        // Emit code to convert a scalar integer or float value
        // to an Integer or Float object, respectively.
        if (type == Predefined::integer_type)
        {
            j_file << "\tinvokestatic\tjava/lang/Integer.valueOf(I)"
                   << "Ljava/lang/Integer;"
                   << endl;
        }
        else
        {
            j_file << "\tinvokestatic\tjava/lang/Float.valueOf(F)"
                   << "Ljava/lang/Float;"
                   << endl;
        }

        j_file << "\taastore" << endl;  // store the value into the array
    }

    // Emit code to call java.io.PrintStream.printf.
    j_file << "\tinvokevirtual java/io/PrintStream.printf"
           << "(Ljava/lang/String;[Ljava/lang/Object;)"
           << "Ljava/io/PrintStream;"
           << endl;
    j_file << "\tpop" << endl;

    return nullptr;
}

//-------------------------------------------------------
antlrcpp::Any Pass2Visitor::visitIfStmt(Pcl2Parser::IfStmtContext *ctx){
	//Strength reduction!
	//reserve labels so that it is nested if safe!
	unsigned long int branch = ifLabels;
	unsigned long int exit = ifLabels+1;
	bool fElse = false;

	int nStatement = ctx->stmtList().size();
	if (nStatement > 1){
		//has else
		fElse = true;
		ifLabels +=2;
	}else{
		//no else
		fElse = false;
		ifLabels += 1;

	}
	globalBranch = branch;
	ifORLoop = false;
	visit(ctx->expr());
	visitChildren(ctx->stmtList(0));
	if (fElse){
		j_file << "\tgoto " << "is" << exit << endl;
	}
	j_file << "is" << branch << ":" << endl; //else or exit label
	if (fElse){
		visitChildren(ctx->stmtList(1));
		j_file << "is" << exit << ":" << endl; //exit label
	}
    return nullptr;
  }

antlrcpp::Any Pass2Visitor::visitCmprOpExpr(Pcl2Parser::CmprOpExprContext *ctx){
	auto value = visitChildren(ctx);
	TypeSpec *type1 = ctx->expr(0)->type;
	TypeSpec *type2 = ctx->expr(1)->type;

	bool integer_mode =    (type1 == Predefined::integer_type)
	                        && (type2 == Predefined::integer_type);
	bool real_mode    =    (type1 == Predefined::real_type)
	                        && (type2 == Predefined::real_type);

	//get operation
	string op = ctx->cmprOp()->getText();
	string out;
	/*switch (op){
	case ">": out = integer_mode?"if_icmple":real_mode?"if_fcmple": "if_?cmple"; break;
	case ">=":
	case "=>":out = integer_mode?"if_icmplt":real_mode?"if_fcmplt": "if_?cmplt"; break;
	case "<=":
	case "=<":out = integer_mode?"if_icmpgt":real_mode?"if_fcmpgt": "if_?cmpgt"; break;
	case "<": out = integer_mode?"if_icmpge":real_mode?"if_fcmpge": "if_?cmpge"; break;
	case "==": out = integer_mode?"if_icmpne":real_mode?"if_fcmpne": "if_?cmpne"; break;
	case "!=" : out = integer_mode?"if_icmpeq":real_mode?"if_fcmpeq": "if_?cmpeq"; break;
	default: out = "???";
	}*/


	if (ifORLoop){
		if (op == ">"){
				out = integer_mode?"if_icmpgt":real_mode?"if_fcmpgt": "if_?cmpgt";
			}else if (op == ">=" | op == "=>"){
				out = integer_mode?"if_icmpge":real_mode?"if_fcmpge": "if_?cmpge";

			}else if (op == "<=" | op == "=<"){
				out = integer_mode?"if_icmple":real_mode?"if_fcmple": "if_?cmple";
			}else if (op == "<"){
				out = integer_mode?"if_icmplt":real_mode?"if_fcmplt": "if_?cmplt";

			}else if (op == "=="){
				out = integer_mode?"if_icmpeq":real_mode?"if_fcmpeq": "if_?cmpeq";
			}else if (op == "!="){
				out = integer_mode?"if_icmpne":real_mode?"if_fcmpne": "if_?cmpne";
			}else{
				out = "???";
			}
	}else{
		if (op == ">"){
				out = integer_mode?"if_icmple":real_mode?"if_fcmple": "if_?cmple";
			}else if (op == ">=" | op == "=>"){
				out = integer_mode?"if_icmplt":real_mode?"if_fcmplt": "if_?cmplt";
			}else if (op == "<=" | op == "=<"){
				out = integer_mode?"if_icmpgt":real_mode?"if_fcmpgt": "if_?cmpgt";

			}else if (op == "<"){
				out = integer_mode?"if_icmpge":real_mode?"if_fcmpge": "if_?cmpge";
			}else if (op == "=="){
				out = integer_mode?"if_icmpne":real_mode?"if_fcmpne": "if_?cmpne";
			}else if (op == "!="){
				out = integer_mode?"if_icmpeq":real_mode?"if_fcmpeq": "if_?cmpeq";
			}else{
				out = "???";
			}
	}



	string labeltype;
	labeltype = ifORLoop? " lp": " is";
	j_file << "\t" << out << labeltype << globalBranch << endl;

	return nullptr;
}

antlrcpp::Any Pass2Visitor::visitKeepGoingStmt(Pcl2Parser::KeepGoingStmtContext *ctx){
	unsigned long int branch = loopLabels;
	j_file << "lp" << loopLabels++ << ":" << endl;
	visit(ctx->stmtList());
	globalBranch = branch;
	ifORLoop = true;
	visit(ctx->expr());
	return nullptr;
}




