# LundPlane

Split MC closure test scrips: UnfoldClosure_(x,y,z).C evaluates the closure in each of the projections of the lund plane 
arguments: UnfoldClosure(std::string file, std::string var, std::string sd, std::string date, int x1, int x2, int y1, int y2)
file = output root file from unfolding the split MC test 
var = "", sd = "" 
date = whatever tag you want to give to the output pdf, I usually put the date so "2_4_21"
x1, x2, y2, y2 = the bins you want to project into in the other axis so for the x projection its the y and z bins, the y projection its the x and z bins, and the z projection it's the x and y bins
example for the x projection: UnfoldClosure("UnfoldSplit_full_Jan29.root", "", "", "2_4_21", 2, 12, 2, 11);
