data = [3754 11751 109742 1697966 26194731 358813933; 
1060 3500 28289 372684 16207242 230059816;
1512 2197 2875 9050 43683 182527];

scale = 2 .^(2:7);

loglog(scale, data(1,:), scale, data(2,:), scale, data(3,:));