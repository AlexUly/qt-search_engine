#include "InvertedIndex.h"
#include "ConverterJSON.h"
#include "SearchEngine.h"

using namespace std;


int main(){
    ConverterJSON conv;
    vector<vector<Entry>> result;
    InvertedIndex in;
    in.UpdateDocumentBase(conv.GetTextDocuments("json/config.json"));
    SearchServer s(in);
    s.config.putAnswers(s.search(conv.GetRequests("json/requests.json")));
    return 0;

}
