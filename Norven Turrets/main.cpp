#include "Hybris.h"
#include <QtWidgets/QApplication>

#include "Service.h"
#include "MemoryRepository.h"
#include "FileRepository.h"

#include "GUI.h"

#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	string repository_path, mylist_path;
	ifstream configuration_file("settings.txt");
	if (!configuration_file.is_open())
		return 0;


	getline(configuration_file, repository_path);
	getline(configuration_file, mylist_path);
	if (repository_path == "memory")
	{
		MemoryRepository repository{};
		TurretValidator validator{};
		
		if (mylist_path == "memory")
		{
			MemoryMyList mylist;
			Service service{ repository, validator, mylist };

			MylistModel* model = new MylistModel{ mylist };
			MylistView list_view{ model };
			GUI gui{ service, &list_view };
			gui.show();

			return a.exec();
		}
		
		else
		{
			string extension = mylist_path.substr(mylist_path.size() - 4);
			if (extension == "html")
			{
				HTMLmylist mylist{ mylist_path };
				Service service{ repository, validator, mylist };

				MylistModel* model = new MylistModel{ mylist };
				MylistView list_view{ model };
				GUI gui{ service, &list_view };
				gui.show();

				return a.exec();
			}
			else if (extension == ".csv")
			{
				CSVmylist mylist{ mylist_path };
				Service service{ repository, validator, mylist };

				MylistModel* model = new MylistModel{ mylist };
				MylistView list_view{ model };
				GUI gui{ service, &list_view };
				gui.show();

				return a.exec();
			}
		}
	}
	else
	{
		FileRepository repository{};
		repository.set_file(repository_path);
		TurretValidator validator{};
		
		if (mylist_path == "memory")
		{
			MemoryMyList mylist;
			Service service{ repository, validator, mylist };

			MylistModel* model = new MylistModel{ mylist };
			MylistView list_view{ model };
			GUI gui{ service, &list_view };
			gui.show();

			return a.exec();
		}

		else
		{
			string extension = mylist_path.substr(mylist_path.size() - 4);
			if (extension == "html")
			{
				HTMLmylist mylist{ mylist_path };
				Service service{ repository, validator, mylist };

				MylistModel* model = new MylistModel{ mylist };
				MylistView list_view{ model };
				GUI gui{ service, &list_view };
				gui.show();

				return a.exec();
			}
			else if (extension == ".csv")
			{
				CSVmylist mylist{ mylist_path };
				Service service{ repository, validator, mylist };

				MylistModel* model = new MylistModel{ mylist };
				MylistView list_view{ model };
				GUI gui{ service, &list_view };
				gui.show();

				return a.exec();
			}
		}

	}
	
}
