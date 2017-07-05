#include <iostream>
#include <random>
#include <map>
#include <fstream>

#include <mgl2/mgl.h>

/* for MathGL prior v2.x */
//#include <mgl2/mgl_zb.h>
//#include <mgl2/mgl_eps.h>
//#include <mgl2/mgl_data.h>


int main(void)
{
	float fGenerated;
	std::map<float,int> mCounts;

	std::default_random_engine generator;
	std::poisson_distribution<int> distribution(5.0);

	for(int i=0;i<1000000;i++)
	{
		fGenerated = distribution(generator);
		mCounts[fGenerated] = mCounts[fGenerated]+1;
	}

	std::string sFile("probability");
	std::ofstream ostOutput(sFile+".txt");	

	for(std::map<float,int>::iterator it=mCounts.begin(); it!=mCounts.end();++it)
	{
	    ostOutput << it->first << "\t" << it->second << std::endl;
	}

    //mglGraph *graph = new mglGraphZB; // for MathGL prior v2.x
    mglGraph *graph = new mglGraph;  // for MathGL 2.x
	mglData datos((sFile+".txt").c_str());

    /* For MathGL prior v2.x
	graph->Transparent=false;
	graph->XRange(datos.SubData(0));	
	graph->YRange(datos.SubData(1));
    */
	graph->SetRange('x',datos.SubData(0));	
	graph->SetRange('y',datos.SubData(1));

	graph->Alpha(false);
	graph->Light(true);

    graph->Title("Sample PNG");

	graph->SubPlot(1,1,0,"^"); // Reserve aditional space only on the upper side  Default value is "<>_^" 
	
	graph->Box(); // The bounding box. Note that putting this on a line before SubPlot will give an unbounded graph (box undersized)
	
	graph->Plot(datos.SubData(0),datos.SubData(1),"r#o ");
	graph->WritePNG((sFile+".png").c_str(),"",false);
	delete graph;	

	return 0;
}
