/** 
                   _ooOoo_ 
                  o8888888o 
                  88" . "88 
                  (| -_- |) 
                  O\  =  /O 
               ____/`---'\____ 
             .'  \\|     |//  `. 
            /  \\|||  :  |||//  \ 
           /  _||||| -:- |||||-  \ 
           |   | \\\  -  /// |   | 
           | \_|  ''\---/''  |   | 
           \  .-\__  `-`  ___/-. / 
         ___`. .'  /--.--\  `. . __ 
      ."" '<  `.___\_<|>_/___.'  >'"". 
     | | :  `- \`.;`\ _ /`;.`/ - ` : | | 
     \  \ `-.   \_ __\ /__ _/   .-` /  / 
======`-.____`-.___\_____/___.-`____.-'====== 
                   `=---=' 
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ 
         佛祖保佑       永无BUG 
*/
//
// Created by steve on 18-3-27.
//

#include <vtkVersion.h>
#include <vtkSmartPointer.h>

#include <vtkChartXY.h>
#include <vtkContextScene.h>
#include <vtkContextView.h>
#include <vtkFloatArray.h>
#include <vtkPlotPoints.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkTable.h>
#include <vtkAutoInit.h>

#include <iostream>
#include <thread>


#include <unistd.h>
#include <vtkVariantArray.h>
#include <vtkDoubleArray.h>

class vtkTimerCallback : public vtkCommand {
public:
    static vtkTimerCallback *New() {
        vtkTimerCallback *cb = new vtkTimerCallback;
        cb->TimerCount = 0;

        // Create a table with some points in it...



        return cb;
    }

    virtual void Execute(vtkObject *vtkNotUsed(caller), unsigned long eventId,
                         void *vtkNotUsed(callData)) {
        if (vtkCommand::TimerEvent == eventId) {
            auto chart = this->chart_;
            vtkPlot *points = chart->AddPlot(vtkChart::POINTS);
            ++this->TimerCount;
//            for (int j(numPoints - 1); j < numPoints * 10; ++j) {
            int j = this->TimerCount + numPoints-1;
            if(j<numPoints *110){

                chart->ClearPlots();
//                table->SetValue(j, 0, j * inc);
//                table->SetValue(j, 1, cos(j * inc) + 0.0);
//                table->SetValue(j, 2, sin(j * inc) + 0.0);
//                table->SetValue(j, 3, sin(j * inc) - cos(j * inc));
                double *tmp_d = new double[4];
                tmp_d[0] = j*inc;
                tmp_d[1] = cos(j*inc);
                tmp_d[2] = sin(j*inc);
                tmp_d[3] = sin(j*inc) - cos(j*inc);
                auto *dd= vtkVariantArray::New();
                dd->Allocate(4);
                dd->Allocate(4);
                dd->SetValue(0,tmp_d[0]);
//                dd->SetValue(1,tmp_d[1]);
//                dd->SetValue(2,tmp_d[2]);
//                dd->SetValue(3,tmp_d[3]);
                table->InsertNextRow(dd);


                for (int k(1); k < 4; ++k) {

                    points = chart->AddPlot(vtkChart::POINTS);
                    points->SetInputData(table, 0, k);
                    points->SetColor(k * 20, k * 20, k * 20);
                    points->SetWidth(1.0);
                    vtkPlotPoints::SafeDownCast(points)->SetMarkerStyle(vtkPlotPoints::CIRCLE);
                }
                std::cout << "aaa" << std::endl;
            view->GetRenderWindow()->Render();
//                view->GetInteractor()->Modified();
//            view->GetRenderWindow()->Modified();
//                view->Modified();
//            view->GetRenderer()->AddObserver()
//                chart->Modified();
                chart->Modified();
                view->Modified();

            }else{
//                view->GetInteractor()->RemoveAllObservers();
//                view->GetInteractor()->Initialize();
//                view->GetInteractor()->Start();
//                view->GetInteractor()->StartPanEvent();
//                view->GetInteractor()->Start();
//                view->Modified();
//                view->
                view->Modified();


            }

//        usleep(1);


//            }
        }

        cout << this->TimerCount << endl;
    }

    vtkSmartPointer<vtkChartXY> chart_;
    int numPoints = 40;
    float inc = 7.5 / (numPoints - 1);
    vtkSmartPointer<vtkTable> table =
            vtkSmartPointer<vtkTable>::New();
    vtkSmartPointer<vtkContextView> view;
private:
    int TimerCount;

};

int main(int, char *[]) {
    // Set up a 2D scene, add an XY chart to it
    vtkSmartPointer<vtkContextView> view =
            vtkSmartPointer<vtkContextView>::New();
    view->GetRenderer()->SetBackground(1.0, 1.0, 1.0);
    view->GetRenderWindow()->SetSize(400, 300);

    vtkSmartPointer<vtkChartXY> chart =
            vtkSmartPointer<vtkChartXY>::New();
    view->GetScene()->AddItem(chart);
    chart->SetShowLegend(true);

    // Create a table with some points in it...
    vtkSmartPointer<vtkTable> table =
            vtkSmartPointer<vtkTable>::New();

    vtkSmartPointer<vtkFloatArray> arrX =
            vtkSmartPointer<vtkFloatArray>::New();
    arrX->SetName("X Axis");
    table->AddColumn(arrX);

    vtkSmartPointer<vtkFloatArray> arrC =
            vtkSmartPointer<vtkFloatArray>::New();
    arrC->SetName("Cosine");
    table->AddColumn(arrC);

    vtkSmartPointer<vtkFloatArray> arrS =
            vtkSmartPointer<vtkFloatArray>::New();
    arrS->SetName("Sine");
    table->AddColumn(arrS);

    vtkSmartPointer<vtkFloatArray> arrT =
            vtkSmartPointer<vtkFloatArray>::New();
    arrT->SetName("Sine - Cosine");
    table->AddColumn(arrT);

    // Test charting with a few more points...
    int numPoints = 40;
    float inc = 7.5 / (numPoints - 1);
    table->SetNumberOfRows(numPoints);
//    table->InsertNextRow()
    for (int i = 0; i < numPoints; ++i) {
        table->SetValue(i, 0, i * inc);
        table->SetValue(i, 1, cos(i * inc) + 0.0);
        table->SetValue(i, 2, sin(i * inc) + 0.0);
        table->SetValue(i, 3, sin(i * inc) - cos(i * inc));
    }

    // Add multiple scatter plots, setting the colors etc
    vtkPlot *points = chart->AddPlot(vtkChart::POINTS);
//#if VTK_MAJOR_VERSION <= 5
//    points->SetInput(table, 0, 1);
//#else
//    points->SetInputData(table, 0, 1);
//#endif
//    points->SetColor(0, 0, 0, 255);
//    points->SetWidth(1.0);
//    vtkPlotPoints::SafeDownCast(points)->SetMarkerStyle(vtkPlotPoints::CROSS);
//
//    points = chart->AddPlot(vtkChart::POINTS);
//#if VTK_MAJOR_VERSION <= 5
//    points->SetInput(table, 0, 2);
//#else
//    points->SetInputData(table, 0, 2);
//#endif
//    points->SetColor(0, 0, 0, 255);
//    points->SetWidth(1.0);
//    vtkPlotPoints::SafeDownCast(points)->SetMarkerStyle(vtkPlotPoints::PLUS);
//
//    points = chart->AddPlot(vtkChart::POINTS);
//#if VTK_MAJOR_VERSION <= 5
//    points->SetInput(table, 0, 3);
//#else
//    points->SetInputData(table, 0, 3);
//#endif
//    points->SetColor(0, 0, 255, 255);
//    points->SetWidth(1.0);
//    vtkPlotPoints::SafeDownCast(points)->SetMarkerStyle(vtkPlotPoints::CIRCLE);

    //Finally render the scene
//    view->GetRenderWindow()->SetMultiSamples(10);
//    view->GetInteractor()->Initialize();
//    view->GetInteractor()->Render();
//    view->GetRenderWindow()->Render();
//    view->GetInteractor()->AddObserver()

//    std::thread at([&]() {
//        view->GetInteractor()->Initialize();
//        view->GetInteractor()->Start();
//    });
//    at.detach();

    auto func = [&]() {

        for (int j(numPoints - 1); j < numPoints * 10; ++j) {
            chart->ClearPlots();
            table->SetValue(j, 0, j * inc);
            table->SetValue(j, 1, cos(j * inc) + 0.0);
            table->SetValue(j, 2, sin(j * inc) + 0.0);
            table->SetValue(j, 3, sin(j * inc) - cos(j * inc));


            for (int k(1); k < 4; ++k) {

                points = chart->AddPlot(vtkChart::POINTS);
                points->SetInputData(table, 0, k);
                points->SetColor(k * 20, k * 20, k * 20);
                points->SetWidth(1.0);
                vtkPlotPoints::SafeDownCast(points)->SetMarkerStyle(vtkPlotPoints::CIRCLE);
            }
            std::cout << "aaa" << std::endl;
//            view->GetRenderWindow()->Render();
            view->GetInteractor()->Modified();
//            view->GetRenderWindow()->Modified();
            view->Modified();
//            view->GetRenderer()->AddObserver()
//            chart->Modified();

//        usleep(1);
            sleep(1);

            usleep(10000);

        }
    };
//    t.detach();

    // Sign up to receive TimerEvent

    auto interactor = view->GetInteractor();
    interactor->Initialize();
    vtkSmartPointer<vtkTimerCallback> cb =
            vtkSmartPointer<vtkTimerCallback>::New();
//    cb->SetC
    cb->chart_ = chart;
    cb->table = table;
    cb->view = view;
    interactor->AddObserver(vtkCommand::TimerEvent, cb,10.0);
//    chart->AddObserver(vtkCommand::TimerEvent,cb);
//    view->GetRenderer()->
//    view->GetRenderer()->AddObserver(vtkCommand::TimerEvent,cb,10.0);
//    view->AddObserver(vtkCommand::TimerEvent,cb);

    int timerId = interactor->CreateRepeatingTimer(100);
//    int timerId = view->GetRenderer()->Tim
    std::cout << "timerId: " << timerId << std::endl;

    view->GetInteractor()->Start();


    double a(0);
    std::cin >> a;

    return EXIT_SUCCESS;
}