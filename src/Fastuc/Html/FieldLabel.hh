<?hh // strict
namespace Fastuc\Html;

abstract class FieldLabel
{
	protected $labelText;
	protected $field;

	public function __construct( $labelText, \Fastuc\Html\Field $field )
	{
		$this->labelText = $labelText;
		$this->field = $field;
	}

	/**
	 * @return string
	 */
	abstract public function toHtml();

	public function __toString()
	{
		return $this->toHtml();
	}
}

