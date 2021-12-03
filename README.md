# LundPlane

**the RooSimple3DPbPb_match.cxx must be ran over all the MC files

RooSimple3DPbPb_match(TString cFiles2="files1.txt", std::string tag = "", std::string date = "", int pthard = 1)
//list arguments 
cFiles2: the list of MC files
tag: way to specify different systematics vs. the nominal result. "nom" run the nominal setting which should be good for now 
date: a way to date the output files (you could put anything here, just a way I used to name files and keep track of output)
pthard: a way to specify which pthard bin you are using in the analysis, it is only used to name the output file so not really needed 

line 164: put the name of your data output here 
line 172: used for an unfolding systematic for reweighting the response

**Unfolding

In order to perform the unfolding, the RooSimple3DPbPb_match.cxx must be ran over all the MC files. Then the output should added together and the unfolding is performed using Unfold.C. Here the arguments are file_data and file_mc. The file_mc is the combined file. The file_data is one of the individual files before adding them together (since the data is ran over each time and we only need to access the data once). 

**Split MC closure test scripts: UnfoldClosure_(x,y,z).C evaluates the closure in each of the projections of the lund plane

arguments: UnfoldClosure(std::string file, std::string var, std::string sd, std::string date, int x1, int x2, int y1, int y2)

file = output root file from unfolding the split MC test 

var = "", sd = "" 

date = whatever tag you want to give to the output pdf, I usually put the date so "2_4_21"

x1, x2, y2, y2 = the bins you want to project into in the other axis so for the x projection its the y and z bins, the y projection its the x and z bins, and the z projection it's the x and y bins

example for the x projection: UnfoldClosure("UnfoldSplit_full_Jan29.root", "", "", "2_4_21", 2, 12, 2, 11);

----------------------------------------------------------------------------------------------------------------------

**Unfolding vs. n_iter scripts: UnfoldIter3D_(x,y,x).C looks at the unfolding stability by comparing the unfolding at different n_iter to n_iter=5 in each projection of the lund plane

arguments: UnfoldIter(std::string file, std::string sd, std::string date, int x1, int x2, int y1, int y2)

file = output root file from unfolding 

sd = ""

date = whatever tag you want to give to the output pdf, I usually put the date so "2_4_21"

x1, x2, y2, y2 = the bins you want to project into in the other axis so for the x projection its the y and z bins, the y projection its the x and z bins, and the z projection it's the x and y bins

example for the x projection: UnfoldIter("Unfold_nom_full_Jan29.root", "", "2_4_21", 2, 12, 2, 11);
