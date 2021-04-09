#pragma once
#include "CommandFactory.hpp"
#include <Acousmoscribe/Model/SpectralKey.hpp>
#include <Process/TimeValue.hpp>
#include <score/tools/Unused.hpp>
#include <QVector>

#include <score/model/path/Path.hpp>

namespace Acousmoscribe
{
class Model;

class ChangeSpectralKeyNature final : public score::Command
{
  SCORE_COMMAND_DECL(Acousmoscribe::CommandFactoryName(), ChangeSpectralKeyNature, "Change the nature of a spectral key")
public:
  ChangeSpectralKeyNature(const Model& model, const Id<SpectralKey>& to_update, Nature nature);

  void undo(const score::DocumentContext& ctx) const override;
  void redo(const score::DocumentContext& ctx) const override;

  void update(unused_t, unused_t, Nature nature);

protected:
  void serializeImpl(DataStreamInput& s) const override;
  void deserializeImpl(DataStreamOutput& s) override;

private:
  Path<Model> m_model;
  QPair<Id<SpectralKey>, SpectralKeyData> m_before, m_after;
};


class ChangeSpectralKeyNature2 final : public score::Command
{
  SCORE_COMMAND_DECL(Acousmoscribe::CommandFactoryName(), ChangeSpectralKeyNature2, "Change the nature2 of a spectral key")
public:
  ChangeSpectralKeyNature2(const Model& model, const Id<SpectralKey>& to_update, Nature nature2);

  void undo(const score::DocumentContext& ctx) const override;
  void redo(const score::DocumentContext& ctx) const override;

  void update(unused_t, unused_t, Nature nature2);

protected:
  void serializeImpl(DataStreamInput& s) const override;
  void deserializeImpl(DataStreamOutput& s) override;

private:
  Path<Model> m_model;
  QPair<Id<SpectralKey>, SpectralKeyData> m_before, m_after;
};


class ChangeSpectralKeyIsRich final : public score::Command
{
  SCORE_COMMAND_DECL(Acousmoscribe::CommandFactoryName(), ChangeSpectralKeyIsRich, "Change the isRich of a spectral key")
public:
  ChangeSpectralKeyIsRich(const Model& model, const Id<SpectralKey>& to_update, bool isRich);

  void undo(const score::DocumentContext& ctx) const override;
  void redo(const score::DocumentContext& ctx) const override;

  void update(unused_t, unused_t, bool isRich);

protected:
  void serializeImpl(DataStreamInput& s) const override;
  void deserializeImpl(DataStreamOutput& s) override;

private:
  Path<Model> m_model;
  QPair<Id<SpectralKey>, SpectralKeyData> m_before, m_after;
};


class ChangeSpectralKeyIsRich2 final : public score::Command
{
  SCORE_COMMAND_DECL(Acousmoscribe::CommandFactoryName(), ChangeSpectralKeyIsRich2, "Change the isRich2 of a spectral key")
public:
  ChangeSpectralKeyIsRich2(const Model& model, const Id<SpectralKey>& to_update, bool isRich2);

  void undo(const score::DocumentContext& ctx) const override;
  void redo(const score::DocumentContext& ctx) const override;

  void update(unused_t, unused_t, bool isRich2);

protected:
  void serializeImpl(DataStreamInput& s) const override;
  void deserializeImpl(DataStreamOutput& s) override;

private:
  Path<Model> m_model;
  QPair<Id<SpectralKey>, SpectralKeyData> m_before, m_after;
};


class ChangeSpectralKeyWarped final : public score::Command
{
  SCORE_COMMAND_DECL(Acousmoscribe::CommandFactoryName(), ChangeSpectralKeyWarped, "Change the isRich of a spectral key")
public:
  ChangeSpectralKeyWarped(const Model& model, const Id<SpectralKey>& to_update, bool isWarped);

  void undo(const score::DocumentContext& ctx) const override;
  void redo(const score::DocumentContext& ctx) const override;

  void update(unused_t, unused_t, bool isWarped);

protected:
  void serializeImpl(DataStreamInput& s) const override;
  void deserializeImpl(DataStreamOutput& s) override;

private:
  Path<Model> m_model;
  QPair<Id<SpectralKey>, SpectralKeyData> m_before, m_after;
};



class ChangeSpectralKeyWarped2 final : public score::Command
{
  SCORE_COMMAND_DECL(Acousmoscribe::CommandFactoryName(), ChangeSpectralKeyWarped2, "Change the isRich of a spectral key")
public:
  ChangeSpectralKeyWarped2(const Model& model, const Id<SpectralKey>& to_update, bool isWarped2);

  void undo(const score::DocumentContext& ctx) const override;
  void redo(const score::DocumentContext& ctx) const override;

  void update(unused_t, unused_t, bool isWarped2);

protected:
  void serializeImpl(DataStreamInput& s) const override;
  void deserializeImpl(DataStreamOutput& s) override;

private:
  Path<Model> m_model;
  QPair<Id<SpectralKey>, SpectralKeyData> m_before, m_after;
};


class ChangeSpectralKeyIsHybrid final : public score::Command
{
  SCORE_COMMAND_DECL(Acousmoscribe::CommandFactoryName(), ChangeSpectralKeyIsHybrid, "Change the isHybrid of a spectral key")
public:
  ChangeSpectralKeyIsHybrid(const Model& model, const Id<SpectralKey>& to_update, bool isHybrid);

  void undo(const score::DocumentContext& ctx) const override;
  void redo(const score::DocumentContext& ctx) const override;

  void update(unused_t, unused_t, bool isHybrid);

protected:
  void serializeImpl(DataStreamInput& s) const override;
  void deserializeImpl(DataStreamOutput& s) override;

private:
  Path<Model> m_model;
  QPair<Id<SpectralKey>, SpectralKeyData> m_before, m_after;
};


class ChangeSpectralKeyIsHybrid2 final : public score::Command
{
  SCORE_COMMAND_DECL(Acousmoscribe::CommandFactoryName(), ChangeSpectralKeyIsHybrid2, "Change the isHybrid2 of a spectral key")
public:
  ChangeSpectralKeyIsHybrid2(const Model& model, const Id<SpectralKey>& to_update, bool isHybrid2);

  void undo(const score::DocumentContext& ctx) const override;
  void redo(const score::DocumentContext& ctx) const override;

  void update(unused_t, unused_t, bool isHybrid2);

protected:
  void serializeImpl(DataStreamInput& s) const override;
  void deserializeImpl(DataStreamOutput& s) override;

private:
  Path<Model> m_model;
  QPair<Id<SpectralKey>, SpectralKeyData> m_before, m_after;
};



}
