#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

vector<pair<int,int>> rotationDelta;
vector<vector<int>> cameraDeltaIndex;

class Camera{
    int row;
    int column;
    int cameraMode;
    int rotationMode;

public:
    Camera(int row, int column, int cameraMode)
    {
        this->row = row;
        this->column = column;
        this->cameraMode = cameraMode;
    }

    pair<int,int> GetPosition(){return {row, column};}

    void SetRotationMode(int mode)
    {
        rotationMode = mode;
    }

    int GetRotationMode(){return rotationMode;}

    void FillMap(vector<vector<int>> & map){
        pair<int, int> pos = {row, column};
        auto currentDeltaIndex = cameraDeltaIndex[cameraMode - 1];

        for(auto index : currentDeltaIndex)
        {
            FillLine(map, rotationDelta[(index + rotationMode) % 4], row, column);
        }
    }

    void FillLine(vector<vector<int>> & map, pair<int, int> direction, int row, int column)
    {
        while(true)
        {
            if(row < 0 || row >= map.size() || column < 0 || column >= map[0].size())
                break;
            if(map[row][column] == 6)
                break;

            map[row][column] = 7;

            row += direction.first;
            column += direction.second;            
        }
    }
};

int validate(vector<vector<int>> & map)
{
    int count = 0;
    for(auto & _row : map)
    {
        for(auto & element : _row)
        {
            if(element == 0) ++count;
        }
    }

    return count;
}

int main()
{
    rotationDelta =
    {
        {1,0}, {0,1}, {-1,0}, {0,-1}
    };

    cameraDeltaIndex =
    {
        {
            1,
        },
        {
            1, 3
        },
        {
            1, 2
        },
        {
            0, 1, 3
        },
        {
            0, 1, 2, 3
        }
    };

    int n, m;
    scanf("%d %d",&n,&m);

    int min = n * m;

    vector<vector<int>> map = vector<vector<int>>(n, vector<int>(m));
    vector<Camera> cameras;

    for(int i=0;i<n;++i)
    {
        for(int j=0;j<m;++j)
        {
            scanf("%d",&(map[i][j]));
            if(map[i][j] > 0 && map[i][j] < 6) cameras.push_back(Camera(i, j, map[i][j]));
        }
    }

    unsigned long long totalCameraMode = 0;

    for(totalCameraMode = 0ULL; totalCameraMode < (1ULL << (2ULL * cameras.size())); ++totalCameraMode)
    {
        unsigned long long currentMode = totalCameraMode;

        int index = 0;
        while(currentMode != 0)
        {
            int maskedCameraMode = currentMode & 0x03;

            cameras[index].SetRotationMode(maskedCameraMode);

            ++index;
            currentMode = currentMode >> 2ULL;
        }

        auto _map = vector<vector<int>>(map);
        for(auto camera : cameras)
        {
            camera.FillMap(_map);
        }

        // TODO : validate '0' block cout in _map
        int new_min = validate(_map);
        if(min > new_min) min = new_min;
    }
    
    printf("%d\n", min);

    return 0;
}