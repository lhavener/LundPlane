# LundPlane

# Split MC closure test scripts: UnfoldClosure_(x,y,z).C evaluates the closure in each of the projections of the lund plane

arguments: UnfoldClosure(std::string file, std::string var, std::string sd, std::string date, int x1, int x2, int y1, int y2)

file = output root file from unfolding the split MC test 

var = "", sd = "" 

date = whatever tag you want to give to the output pdf, I usually put the date so "2_4_21"

x1, x2, y2, y2 = the bins you want to project into in the other axis so for the x projection its the y and z bins, the y projection its the x and z bins, and the z projection it's the x and y bins

example for the x projection: UnfoldClosure("UnfoldSplit_full_Jan29.root", "", "", "2_4_21", 2, 12, 2, 11);

#Unfolding vs. n_iter scripts: UnfoldIter3D_(x,y,x).C looks at the unfolding stability by comparing the unfolding at different n_iter to n_iter=5 in each projection of the lund plane

arguments: UnfoldIter(std::string file, std::string sd, std::string date, int x1, int x2, int y1, int y2)

file = output root file from unfolding 

sd = ""

date = whatever tag you want to give to the output pdf, I usually put the date so "2_4_21"

x1, x2, y2, y2 = the bins you want to project into in the other axis so for the x projection its the y and z bins, the y projection its the x and z bins, and the z projection it's the x and y bins

example for the x projection: UnfoldIter("Unfold_nom_full_Jan29.root", "", "2_4_21", 2, 12, 2, 11);
