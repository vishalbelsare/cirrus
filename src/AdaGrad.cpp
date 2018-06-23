#include "AdaGrad.h"

namespace cirrus {
  AdaGrad::AdaGrad(double lr, double ae):
       OptimizationMethod(lr), adagrad_epsilon(ae) {}
      std::vector<FEATURE_TYPE> AdaGrad::sgd_update(
          std::vector<FEATURE_TYPE> weights, const ModelGradient* gradient) {
        int64_t size = static_cast<int64_t>(weights_hist_.size());
        if (size == 0) {
          weights_hist_.resize(static_cast<int64_t>(weights.size()));
        }
        const LRSparseGradient* grad =
          dynamic_cast<const LRSparseGradient*>(gradient);

        if (grad == nullptr) {
          throw std::runtime_error("Error in dynamic cast");
        }

        for (const auto& w : grad->weights) {
           int index = w.first;
           FEATURE_TYPE value = w.second;

          // update history
          FEATURE_TYPE& weight_hist = weights_hist_[index];
          weight_hist += value * value;
          weights[index] += learning_rate * value /
          (adagrad_epsilon + std::sqrt(weight_hist));
        }
        return weights;
      }
}
