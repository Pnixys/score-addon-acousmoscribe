#pragma once
#include "CommandFactory.hpp"
#include <Acousmoscribe/Model/Sign.hpp>
#include <Process/TimeValue.hpp>

#include <score/model/path/Path.hpp>

namespace Acousmoscribe{

class Model;

class RemoveSigns final : public score::Command
{
    SCORE_COMMAND_DECL(Acousmoscribe::CommandFactoryName(), RemoveSigns, "Remove Signs")
public:
    RemoveSigns(const Model& model, const std::vector<Id<Sign>>& to_remove);

    void undo(const score::DocumentContext& ctx) const override;
    void redo(const score::DocumentContext& ctx) const override;

protected:
    void serializeImpl(DataStreamInput& s) const override;
    void deserializeImpl(DataStreamOutput& s) override;

private:
    Path<Model> m_model;
    QVector<QPair<Id<Sign>, SignData>> m_signs;
};
}