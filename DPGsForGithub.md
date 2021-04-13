DPGs and github names
====


Where:

    /afs/cern.ch/user/a/amassiro/work/RC

Names will appear in:

    https://github.com/cms-sw/cms-bot/blob/master/categories.py

    

Procedure:

    scramv1 list -a

get the version

    git clone git@github.com:cms-sw/cms-bot.git

    git clone git@github.com:amassiro/cms-bot.git
    
modify file:

    categories.py
    
    
Create PR:

    git remote add origin git@github.com:amassiro/cms-bot

    git fetch origin

    git checkout -b  add-dpgs-to-categories
    
    git commit ...
       
    git push -u origin  add-dpgs-to-categories
    
    
Then on the web for the PR

    https://github.com/cms-sw/cms-bot/pull/1532
    
    
    
    
    
    
