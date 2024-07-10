#include <iostream>
#include <sstream>
#include <deque>
#include <map>
using namespace std;
class Patient
{
private:
	string name; int status;
public:
	Patient() = default;
	Patient(string name, int status) : name(name), status(status)
	{

	}
	const string& GetName() const
	{
		return name;
	}
	const int& IsUrgent()
	{
		return status;
	}
	string ToString()
	{
		ostringstream oss;
		oss << name << " ";
		if (IsUrgent())
			oss << "Urgent";
		else
			oss << "Regular";
		oss << endl;
		return oss.str();
	}
};
class Specializaton
{
private:
	string name;
	int max_patients_queue_size = 5, spec_num;
	deque<Patient> patients;
	void RemovePatient()
	{
		patients.pop_front();
	}
public:
	Specializaton() = default;
	Specializaton(int spec_num, string name, deque<Patient> d = {}) :spec_num(spec_num), name(name)
	{

	}
	void AddPatient( Patient& patient)
	{
		if (patients.size() < GetMaxQueueSize())
		{
			if (patient.IsUrgent())
				patients.push_front(patient);
			else
				patients.push_back(patient);
		}
		else
		{
			cout << "\nWe apologize , Queue is currently full\n";
		}
	}
	
	void GetCurrentPatient()
	{
		if (patients.empty())
		{
			cout << "\nNo patients at the moment. Have a rest , Dr\n";
			return;
		}
		cout << patients.front().GetName() << ",Go with the doctor";
		RemovePatient();
	}
	void PrintPatients()
	{
		if (patients.empty())
			return;
		cout << "Specialization " << GetName() << " " << GetSpecNum() << endl;
		for (auto patient : patients)
		{
			cout << patient.ToString();
		}
		cout << "\n\n";
	}
	int GetMaxQueueSize()
	{
		return max_patients_queue_size;
	}
	int GetSpecNum()
	{
		return spec_num;
	}
	string GetName()
	{
		return name;
	}
};
class SpecializationManager
{
private:
	map<int, Specializaton> mp_specnum_spec;
	SpecializationManager()
	{
		LoadSpecializations();
	};
public:
	static SpecializationManager  s;
	static SpecializationManager& GetInstance()
	{
		//if(s == nullptr)
		s =  SpecializationManager();
		return s;
	}
	 Specializaton* GetSpecialization(int specnum)
	{
		return &mp_specnum_spec[specnum];
	}
	 void PrintAllSpecializations()
	 {
		 for (auto& pair : mp_specnum_spec)
		 {
			 pair.second.PrintPatients();
		    
		 }
	 }
	void LoadSpecializations()
	{
		Specializaton s = Specializaton(1, "Surgery");
		mp_specnum_spec.insert({ s.GetSpecNum() , s });
		s = Specializaton(2, "Children");
		mp_specnum_spec.insert({ s.GetSpecNum() , s });
		s = Specializaton(3, "Eyes");
		mp_specnum_spec.insert({ s.GetSpecNum() , s });
		s = Specializaton(4, "Neural");
		mp_specnum_spec.insert({ s.GetSpecNum() , s });
		s = Specializaton(5, "Bones");
		mp_specnum_spec.insert({ s.GetSpecNum() , s });
		s = Specializaton(6, "Liver");
		mp_specnum_spec.insert({ s.GetSpecNum() , s });
		s = Specializaton(7, "Pathology");
		mp_specnum_spec.insert({ s.GetSpecNum() , s });
		s = Specializaton(8, "MotherHood");
		mp_specnum_spec.insert({ s.GetSpecNum() , s });
		s = Specializaton(9, "Anesthesiology");
		mp_specnum_spec.insert({ s.GetSpecNum() , s });
		s = Specializaton(10, "Cardiology");
		mp_specnum_spec.insert({ s.GetSpecNum() , s });
		s = Specializaton(11, "Dermatology");
		mp_specnum_spec.insert({ s.GetSpecNum() , s });
		s = Specializaton(12, "Emergency Medicine");
		mp_specnum_spec.insert({ s.GetSpecNum() , s });
		s = Specializaton(13, "Family Medicine");
		mp_specnum_spec.insert({ s.GetSpecNum() , s });
		s = Specializaton(14, "Forensic Pathology");
		mp_specnum_spec.insert({ s.GetSpecNum() , s });
		s = Specializaton(15, "General Surgery");
		mp_specnum_spec.insert({ s.GetSpecNum() , s });
		s = Specializaton(16, "Hospital Medicine");
		mp_specnum_spec.insert({ s.GetSpecNum() , s });
		s = Specializaton(17, "Genetics and Genomics");
		mp_specnum_spec.insert({ s.GetSpecNum() , s });
		s = Specializaton(18, "Orthopaedic Surgery");
		mp_specnum_spec.insert({ s.GetSpecNum() , s });
		s = Specializaton(19, "psychiatry ");
		mp_specnum_spec.insert({ s.GetSpecNum() , s });
		s = Specializaton(20, "Radiology");
		mp_specnum_spec.insert({ s.GetSpecNum() , s });
	}

};
SpecializationManager SpecializationManager::s = SpecializationManager();
class Doctor
{
private:
	string name; SpecializationManager& sManager;
public:
	Doctor(string name) :name(name), sManager(SpecializationManager::GetInstance())
	{

	}
	void DisplayWelcome()
	{
		cout << "Welcome, Dr " << name << endl;
	}
	void GetNextpatient()
	{
		cout << "Enter Specialization: ";
		int spec;
		cin >> spec;
		Specializaton * current_spec = sManager.GetSpecialization(spec);
		current_spec->GetCurrentPatient();
	}
};
int main()
{
	SpecializationManager& s = SpecializationManager::GetInstance();
	
	Doctor d("Mohamed_Emad");
	d.DisplayWelcome();
	while (true)
	{
	cout << "\n1 - Add new Patient\n\n2 - Print all patients\n\n3 - Get next patient\n\n4 - Exit\n";
	
		int choice;
		cin >> choice;
		if (choice == 1)
		{
			string name;
			int num;
			cout << "Enter specialization: ";
			cin >> num;
			Specializaton*  current_spec =  s.GetSpecialization(num);
			cout << "Enter name & status: ";
			cin >> name >> num;
			Patient p(name, num);
			current_spec->AddPatient(p);
		}
		if (choice == 2)
		{
			s.PrintAllSpecializations();
		}
		if (choice == 3)
		{
			d.GetNextpatient();
		}
		if (choice == 4)
			return 0;

	}
}