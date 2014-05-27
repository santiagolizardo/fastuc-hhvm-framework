<?hh // strict
namespace Fastuc\Html;

class AroundFieldLabel extends \Fastuc\Html\FieldLabel
{
	/**
	 * @return string
	 */
	public function toHtml()
	{
		$html = sprintf( '<label>%s %s</label>', $this->field, $this->labelText );
		return $html;
	}
}


