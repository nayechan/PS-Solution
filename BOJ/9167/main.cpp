#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <list>
#include <sstream>
#include <algorithm>
#include <memory>

using namespace std;

using std::cout;

bool IsValidString(const string& input)
{
	return find_if(input.begin(), input.end(), (int(*)(int))isalnum) != input.end();
}

string ToUpperSentence(const string& input)
{
	string output = input;
	output[0] = toupper(output[0]);

	return output;
}

bool IsTheHolyGrail(const string& input)
{
	list<char> charList = { 't', 'h', 'e', 'h', 'o', 'l', 'y', 'g', 'r', 'a', 'i', 'l' };

	for (char ch : input)
	{
		if (charList.size() == 0) break;
		if (charList.front() == tolower(ch))
		{
			charList.pop_front();
		}
	}

	return charList.size() == 0;
}

class BaseFA {
public:
	virtual string Get() = 0;
};

class FA : public BaseFA {
	int index;
	vector<shared_ptr<BaseFA>> expansion;
public:
	FA(vector<shared_ptr<BaseFA>> _expansion)
	{
		expansion = _expansion;
		index = 0;
	}

	virtual void SetExpansion(vector<shared_ptr<BaseFA>> _expansion) { expansion = _expansion; }

	virtual string Get() override { return expansion[index++ % expansion.size()]->Get(); }
};

class TerminalFA : public BaseFA {
	int index;
	vector<string> expansion;
public:
	TerminalFA(vector<string> _expansion)
	{
		expansion = _expansion;
		index = 0;
	}
	virtual string Get() override { return expansion[index++ % expansion.size()]; }
};

class Taunt : public FA {
	int count;
public:
	Taunt(int _count) : FA(vector<shared_ptr<BaseFA>>()) {
		count = _count;
	}

	Taunt(int _count, vector<shared_ptr<BaseFA>> _expansion) : FA(_expansion) {
		count = _count;
	}

	void SetCount(int _count) { count = _count; }
	int GetCount() { return count; }

	virtual string Get() override {
		--count;
		string result = FA::Get();
		return result;
	}

	string GetChildishHandGesture() {
		--count;
		return "(A childish hand gesture)";
	}
};

class ProcessFA : public BaseFA {
	vector<shared_ptr<BaseFA>> arguments;
	function<string(vector<shared_ptr<BaseFA>>)> handler;

public:
	ProcessFA(vector<shared_ptr<BaseFA>> _arguments, function<string(vector<shared_ptr<BaseFA>>)> _handler)
	{
		arguments = _arguments;
		handler = _handler;
	}
	virtual string Get() override {
		return handler(arguments);
	}
};

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
    cout.tie(NULL);

	shared_ptr<BaseFA> taunt, sentence, noun_phrase, modified_noun, modifier, present_rel,
		past_rel, present_person, past_person, noun, present_verb, past_verb, article, adjective, adverb;

	present_person = make_shared<TerminalFA>(
		vector<string>{"steed", "king", "first-born"}
	);
	past_person = make_shared<TerminalFA>(
		vector<string>{"mother", "father", "grandmother", "grandfather", "godfather"}
	);
	noun = make_shared<TerminalFA>(
		vector<string>{"hamster", "coconut", "duck", "herring", "newt", "peril", "chicken", "vole", "parrot", "mouse", "twit"}
	);
	present_verb = make_shared<TerminalFA>(
		vector<string>{"is", "masquerades as"}
	);
	past_verb = make_shared<TerminalFA>(
		vector<string>{"was", "personified"}
	);
	article = make_shared<TerminalFA>(
		vector<string>{"a"}
	);
	adjective = make_shared<TerminalFA>(
		vector<string>{"silly", "wicked", "sordid", "naughty", "repulsive", "malodorous", "ill-tempered"}
	);
	adverb = make_shared<TerminalFA>(
		vector<string>{"conspicuously", "categorically", "positively", "cruelly", "incontrovertibly"}
	);



	present_rel = make_shared<ProcessFA>(
		vector<shared_ptr<BaseFA>>{present_person, present_verb},
		[](vector<shared_ptr<BaseFA>> arguments) {
			return "your " + arguments[0]->Get() + " " + arguments[1]->Get();
		}
	);

	past_rel = make_shared<ProcessFA>(
		vector<shared_ptr<BaseFA>>{past_person, past_verb},
		[](vector<shared_ptr<BaseFA>> arguments) {
			return "your " + arguments[0]->Get() + " " + arguments[1]->Get();
		}
	);



	modifier = make_shared<FA>(
		vector<shared_ptr<BaseFA>>{
		adjective,
			make_shared<ProcessFA>(vector<shared_ptr<BaseFA>>{adverb, adjective}, [](vector<shared_ptr<BaseFA>> arguments) {
			return arguments[0]->Get() + " " + arguments[1]->Get();
				}),
	}
	);

	modified_noun = make_shared<FA>(
		vector<shared_ptr<BaseFA>>{
		noun,
			make_shared<ProcessFA>(vector<shared_ptr<BaseFA>>{modifier, noun}, [](vector<shared_ptr<BaseFA>> arguments) {
			return arguments[0]->Get() + " " + arguments[1]->Get();
				}),
	}
	);

	noun_phrase = make_shared<ProcessFA>(
		vector<shared_ptr<BaseFA>>{article, modified_noun},
		[](vector<shared_ptr<BaseFA>> arguments) {
			return arguments[0]->Get() + " " + arguments[1]->Get();
		}
	);



	sentence = make_shared<FA>(
		vector<shared_ptr<BaseFA>>{
		make_shared<ProcessFA>(vector<shared_ptr<BaseFA>>{past_rel, noun_phrase}, [](vector<shared_ptr<BaseFA>> arguments) {
			return ToUpperSentence(arguments[0]->Get() + " " + arguments[1]->Get());
			}),
			make_shared<ProcessFA>(vector<shared_ptr<BaseFA>>{present_rel, noun_phrase}, [](vector<shared_ptr<BaseFA>> arguments) {
			return ToUpperSentence(arguments[0]->Get() + " " + arguments[1]->Get());
				}),
			make_shared<ProcessFA>(vector<shared_ptr<BaseFA>>{past_rel, article, noun}, [](vector<shared_ptr<BaseFA>> arguments) {
			return ToUpperSentence(arguments[0]->Get() + " " + arguments[1]->Get() + " " + arguments[2]->Get());
				})
	}
	);

	taunt = make_shared<Taunt>(3);

	static_pointer_cast<Taunt>(taunt)->SetExpansion(
		vector<shared_ptr<BaseFA>>{
		sentence,
			make_shared<ProcessFA>(vector<shared_ptr<BaseFA>>{taunt, sentence}, [](vector<shared_ptr<BaseFA>> arguments) {
			string strA = arguments[0]->Get();
			string strB = arguments[1]->Get();
			return strA + " " + strB;
				}),
			make_shared<ProcessFA>(vector<shared_ptr<BaseFA>>{noun}, [](vector<shared_ptr<BaseFA>> arguments) {
			return ToUpperSentence(arguments[0]->Get() + "!");
				}),
			sentence
	}
	);

	shared_ptr<Taunt> _taunt = static_pointer_cast<Taunt>(taunt);

	string input, output;
	for (; getline(cin, input);)
	{
		istringstream stringStream(input);
		string seperatedInput;
		int n = 0;

		cout << "Knight: ";
		while (stringStream >> seperatedInput) {
			cout << seperatedInput << " ";
			if (IsValidString(seperatedInput))
			{
				++n;
			}
		}
		cout << "\n";
		_taunt->SetCount((n + 2) / 3);

		bool isTheHolyGrail = IsTheHolyGrail(input);

		while (_taunt->GetCount() > 0)
		{
			if (isTheHolyGrail)
			{
				cout << "Taunter: " << _taunt->GetChildishHandGesture() << "."  << "\n";
				isTheHolyGrail = false;
			}
			else
			{
				cout << "Taunter: " << _taunt->Get() << "."  << "\n";
			}
		}
		cout  << "\n";
	}
}