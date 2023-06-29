#pragma once
#include <CppUnitTest.h>
#include <Pulp/Layer.h>
#include <Pulp/LayerStack.h>
#include <vector>

namespace LayerTests {
	using namespace Microsoft::VisualStudio::CppUnitTestFramework;


	TEST_CLASS(LayerTests) {
	public:
		TEST_METHOD(TestLayerConstructor){
			Assert::IsTrue(true);
			class a : public Pulp::Layer {

			};

			Pulp::Layer l("Hello");
			Assert::AreEqual(l.GetName(), std::string("Hello"));
			l = Pulp::Layer();
			Assert::AreEqual(l.GetName(), std::string("Layer"));
		}
	};

	TEST_CLASS(LasyerStackTests) {
	public:
		TEST_METHOD(LayerPushAndPopTest) {
			Pulp::LayerStack ls;
			int expectedSize, actualSize;

			Pulp::Layer* layer1 = new Pulp::Layer("1");
			Pulp::Layer* layer2 = new Pulp::Layer("2");
			Pulp::Layer* layer3 = new Pulp::Layer("3");

			ls.PushLayer(layer1);
			ls.PushLayer(layer2);
			ls.PushLayer(layer3);

			expectedSize = 3;
			actualSize = 0;

			for (auto l : ls) {
				actualSize++;
			}

			Assert::AreEqual(expectedSize, actualSize);

			Assert::IsTrue(std::find(ls.begin(), ls.end(), layer1) != ls.end());
			Assert::IsTrue(std::find(ls.begin(), ls.end(), layer2) != ls.end());
			Assert::IsTrue(std::find(ls.begin(), ls.end(), layer3) != ls.end());


			ls.PopLayer(layer1);

			expectedSize = 2;
			actualSize = 0;

			for (auto l : ls) {
				actualSize++;
			}

			Assert::AreEqual(expectedSize, actualSize);

			Assert::IsFalse(std::find(ls.begin(), ls.end(), layer1) != ls.end());
			Assert::IsTrue(std::find(ls.begin(), ls.end(), layer2) != ls.end());
			Assert::IsTrue(std::find(ls.begin(), ls.end(), layer3) != ls.end());
		}
		TEST_METHOD(OverlayPushAndPopTest) {
			Pulp::LayerStack ls;
			int expectedSize, actualSize;

			Pulp::Layer* overlay1 = new Pulp::Layer("1");
			Pulp::Layer* overlay2 = new Pulp::Layer("2");
			Pulp::Layer* overlay3 = new Pulp::Layer("3");

			ls.PushOverlay(overlay1);
			ls.PushOverlay(overlay2);
			ls.PushOverlay(overlay3);

			expectedSize = 3;
			actualSize = 0;

			for (auto l : ls) {
				actualSize++;
			}

			Assert::AreEqual(expectedSize, actualSize);

			Assert::IsTrue(std::find(ls.begin(), ls.end(), overlay1) != ls.end());
			Assert::IsTrue(std::find(ls.begin(), ls.end(), overlay2) != ls.end());
			Assert::IsTrue(std::find(ls.begin(), ls.end(), overlay3) != ls.end());


			ls.PopOverlay(overlay1);

			expectedSize = 2;
			actualSize = 0;

			for (auto l : ls) {
				actualSize++;
			}

			Assert::AreEqual(expectedSize, actualSize);

			Assert::IsFalse(std::find(ls.begin(), ls.end(), overlay1) != ls.end());
			Assert::IsTrue(std::find(ls.begin(), ls.end(), overlay2) != ls.end());
			Assert::IsTrue(std::find(ls.begin(), ls.end(), overlay3) != ls.end());
		}

		TEST_METHOD(LayerOverlayDisplacementTest) {
			Pulp::LayerStack ls;
			int layerSize;
			int overlaySize;

			Pulp::Layer* layer1 = new Pulp::Layer("layer");
			Pulp::Layer* layer2 = new Pulp::Layer("layer");
			Pulp::Layer* layer3 = new Pulp::Layer("layer");
			layerSize = 3;

			ls.PushLayer(layer1);
			ls.PushLayer(layer2);
			ls.PushLayer(layer3);

			Pulp::Layer* overlay1 = new Pulp::Layer("overlay");
			Pulp::Layer* overlay2 = new Pulp::Layer("overlay");
			Pulp::Layer* overlay3 = new Pulp::Layer("overlay");
			Pulp::Layer* overlay4 = new Pulp::Layer("overlay");
			overlaySize = 4;

			ls.PushOverlay(overlay1);
			ls.PushOverlay(overlay2);
			ls.PushOverlay(overlay3);
			ls.PushOverlay(overlay4);

			auto it = ls.begin();

			for (int i = 0; i < layerSize; i++) {
				Pulp::Layer* l = *it;
				Assert::AreEqual(l->GetName(), std::string("layer"));
				it++;
			}

			for (int i = 0; i < overlaySize; i++) {
				Pulp::Layer* l = *it;
				Assert::AreEqual(l->GetName(), std::string("overlay"));
				it++;
			}

			Assert::IsTrue(it == ls.end());



			ls.PopLayer(layer1);
			layerSize--;
			ls.PopOverlay(overlay1);
			ls.PopOverlay(overlay2);
			ls.PopOverlay(overlay3);
			overlaySize -= 3;

			it = ls.begin();

			for (int i = 0; i < layerSize; i++) {
				Pulp::Layer* l = *it;
				Assert::AreEqual(l->GetName(), std::string("layer"));
				it++;
			}

			for (int i = 0; i < overlaySize; i++) {
				Pulp::Layer* l = *it;
				Assert::AreEqual(l->GetName(), std::string("overlay"));
				it++;
			}

			Assert::IsTrue(it == ls.end());

		}
	};
}