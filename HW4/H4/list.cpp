void listAll(string path, const Domain* d) // two-parameter overload
{
    if (d->subdomains().size() == 0) {
        cout<<path<<endl;
    }
    for (int i = 0; i<d->subdomains().size(); i++) {
        if (path.length() == 0) {
            listAll(d->subdomains()[i]->label(), d->subdomains()[i]);
        }
        else{
            listAll(d->subdomains()[i]->label()+"."+path, d->subdomains()[i]);
        }
    }
}

